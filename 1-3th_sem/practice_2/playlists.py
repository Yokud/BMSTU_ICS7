from cement.core.controller import CementBaseController, expose
from utility import *
import glob, os


class PlaylistsController(CementBaseController):
    class Meta:
        label = 'playlist'
        description = 'Work with playlists'
        stacked_on = 'base'
        stacked_type = 'nested'

        arguments = [
            (['--see', '--list'],
             dict(action='store_true', help='See the current playlist', dest='list')),
            (['--seeall', '--listall'],
             dict(action='store_true', help='See all playlists', dest='listall')),
            (['-a', '--add'],
             dict(action='store_true', help='Add current playlist to all playlists', dest='add')),
            (['-s', '--set'],
             dict(action='store_true', help='Choose the current playlist from all', dest='set')),
            (['-o', '--order'],
             dict(action='store', help='Change songs order in the playlist', dest='order')),
            (['-c', '--clear'],
             dict(action='store_true', help='Clear the current playlist', dest='clear')),
        ]

    @expose(hide=True)
    def default(self):
        if not any([self.app.pargs.list, self.app.pargs.add, self.app.pargs.set, self.app.pargs.clear,
                    self.app.pargs.order,
                    self.app.pargs.listall, ]):
            print('Use subcommands:\n-h     Playlist settings')
            return
        try:
            with open('db_path.txt', 'r') as f:
                path = f.readline()
                if not path:
                    print('You have not chosen your music folder location yet!\n\
Use "path --set" command for that')
                    return
        except:
            print('You have not chosen your music folder location yet!\n\
Use "path --set" command for that')
            return

        if self.app.pargs.clear:
            with open(path + 'musrepl_db/playlist.txt', 'w'):
                pass

        if self.app.pargs.set:
            name = input('Playlist name: ')
            with open(path + 'musrepl_db/playlists.txt', 'r') as playlists:
                if playlists.readline == '':
                    print('You have not added any playlists yet!\nUse subcommand --add')
                else:
                    playlists.seek(0)
                    with open(path + 'musrepl_db/playlist.txt', 'w') as playlist:
                        check = 0
                        for line in playlists:
                            if line == '{}' + name + '{}\n':
                                check = 1
                                continue
                            if check == 1:
                                if line[1] == '{':
                                    break
                                else:
                                    playlist.write(line)

                        if check == 0:
                            print('Error: Cannot find playlist "' + name + '"')
                        else:
                            print('Playlist successfully added')
            return

        if self.app.pargs.list:
            with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                if playlist.readline() == '':
                    print('You have not added tracks to current playlist yet\nUse command "sl"')
                else:
                    playlist.seek(0)
                    print('-' * 10 + 'CURRENT PLAYLIST' + '-' * 10)
                    for line in playlist:
                        print(line, end='')
                    print('\n' + '-' * 36)

        if self.app.pargs.listall:
            with open(path + 'musrepl_db/playlists.txt', 'r') as playlists:
                if playlists.readline() == '':
                    print('You have not added any tracks to your playlists yet\nUse command "sl"')
                else:
                    playlists.seek(0)
                    print('-' * 10 + 'YOUR PLAYLISTS' + '-' * 10)
                    for line in playlists:
                        print(line, end='')
                    print('\n' + '-' * 34)

        if self.app.pargs.order:
            try:
                indexes = self.app.pargs.order.split(',')
                i = 0
                while (i < len(indexes)):
                    if '-' in indexes[i]:
                        v = trstr(indexes[i])
                        indexes[i:i + 1] = v
                        i += len(v) - 1

                    i += 1
                indexes = list(map(int, indexes))

                with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                    if playlist.readline == '':
                        print('You have not added tracks to current playlist yet\nUse command "sl"')
                        return
                    else:
                        playlist.seek(0)
                        lines = playlist.readlines()
                        lines = list(lines[i - 1] for i in indexes)

                with open(path + 'musrepl_db/playlist.txt', 'w') as playlist:
                    index = 1
                    for line in lines:
                        playlist.write(f'{index} {line[line.find(" "):]}')
                        if line[-1] != '\n':
                            playlist.write('\n')
                        index += 1
            except:
                print('Incorrect indexes')

        if self.app.pargs.add:
            with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                if playlist.readline == '':
                    print('You have not added tracks to current playlist yet\nUse command "sl"')
                else:
                    playlist.seek(0)
                    name = input('Playlist name: ')
                    with open(path + 'musrepl_db/playlists.txt', 'a') as playlists:
                        playlists.write('{}' + name + '{}\n')
                        for line in playlist:
                            playlists.write(line)
                            if line[-1] != '\n':
                                playlists.write('\n')