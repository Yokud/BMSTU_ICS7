from cement.core.controller import CementBaseController, expose
from utility import *
import glob, os
from SoundPlayer_class import *
from GUI import *
from tkinter import *

class MusicPlayerController(CementBaseController):
    class Meta:
        label = 'play'
        description = 'Play music'
        stacked_on = 'base'
        stacked_type = 'nested'

        arguments = [
            (['-n', '--number'],
             dict(action='store', help='Play song from search-list with chosen number', dest='number')),
            (['-p', '--playlist'],
             dict(action='store_true', help='Play current playlist', dest='playlist')),
            (['-pn', '--playlistn'],
             dict(action='store', help='Play song from playlist with chosen number', dest='pnumber')),
            (['-sl', '--search-list'],
             dict(action='store_true', help='Play found songs', dest='search')),
        ]

    @expose(hide=True)
    def default(self):
        if not self.app.pargs.number and not self.app.pargs.playlist and not self.app.pargs.search and not self.app.pargs.pnumber and not self.app.pargs.ngnumber:
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

        if self.app.pargs.number:
            number = self.app.pargs.number
            with open(path + 'musrepl_db/search_list.txt', 'r') as search_list:
                check_number = 0
                lines = search_list.readlines()
                for line in lines:
                    if line[:line.find(' ')] == number:
                        check_number = 1
                        window = Tk()
                        if line[-1] == '\n':
                            GUI(window, [path + line[line.find(' ') + 1:len(line) - 1]], 0)
                        else:
                            GUI(window, [path + line[line.find(' ') + 1:]], 0)
                        window.mainloop()
                if check_number == 0:
                    print('No tracks with this number were found')

        if self.app.pargs.playlist:
            with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                lines = playlist.readlines()
                if len(lines) == 0:
                    print('Empty playlist')
                else:
                    for i in range(len(lines)):
                        lines[i] = path + lines[i][lines[i].find(' ') + 1:]
                        if lines[i][-1] == '\n':
                            lines[i] = lines[i][:len(lines[i]) - 1]
                    window = Tk()
                    GUI(window, lines, 0)
                    window.mainloop()

        if self.app.pargs.pnumber:
            number = self.app.pargs.pnumber
            with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                check_number = 0
                lines = playlist.readlines()
                for line in lines:
                    if line[:line.find(' ')] == number:
                        check_number = 1
                        window = Tk()
                        if line[-1] == '\n':
                            GUI(window, [path + line[line.find(' ') + 1:len(line) - 1]], 0)
                        else:
                            GUI(window, [path + line[line.find(' ') + 1:]], 0)
                        window.mainloop()
                if check_number == 0:
                    print('No tracks with this number were found')

        if self.app.pargs.search:
            with open(path + 'musrepl_db/search_list.txt', 'r') as search_list:
                lines = search_list.readlines()
                if len(lines) == 0:
                    print('You haven\'t searched tracks yet\nUse command "search"')
                else:
                    for i in range(len(lines)):
                        lines[i] = path + lines[i][lines[i].find(' ') + 1:]
                        if lines[i][-1] == '\n':
                            lines[i] = lines[i][:len(lines[i]) - 1]
                    window = Tk()
                    GUI(window, lines, 0)
                    window.mainloop()