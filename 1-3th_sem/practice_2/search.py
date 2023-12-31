from cement.core.controller import CementBaseController, expose
from utility import *
import glob, os
import eyed3


class SearchController(CementBaseController):
    class Meta:
        label = 'search'
        description = 'Search for tracks in the folder defined by path'
        stacked_on = 'base'
        stacked_type = 'nested'

        arguments = [
            (['-n', '--name'],
             dict(action='store', help='search for tracks by name', dest='name')),
        ]

    @expose(hide=True)
    def default(self):

        search = ''
        if self.app.pargs.name:
            search = self.app.pargs.name

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

        search_parameters = [None, None, ]

        extensions = [
            'mp3',
            'wav',
            'midi',
        ]

        with open(path + 'musrepl_db/search_list.txt', 'r') as search_file:
            index = get_index(search_file)
        with open(path + 'musrepl_db/search_list.txt', 'a') as search_file:
            print('-' * 10 + 'FOUND TRACKS' + '-' * 10)
            make_search(path, search, search_file, extensions, search_parameters, index)
            print('-' * 32)


class SearchOptions(CementBaseController):
    class Meta:
        label = 'opt'
        description = 'Additional search options.'
        stacked_on = 'search'
        stacked_type = 'nested'

        arguments = [
            (['-n', '--name'],
             dict(action='store', help='Search for tracks by file\'s name', dest='name')),
            (['-a', '--author'],
             dict(action='store', help='Specific author\'s track search', dest='author')),
            (['-l', '--album'],
             dict(action='store', help='Search for tracks from the album', dest='album')),
            (['-c', '--clear'],
             dict(action='store_true', help='Clear the search list before making search', dest='clear')),
            (['-d', '--deep'],
             dict(action='store', help='Set the subfolders\' search deep (1 is default)', dest='deep')),
        ]

    @expose(hide=True)
    def default(self):
        try:
            with open('db_path.txt', 'r') as f:
                path = f.readline()
                if not path:
                    print('You have not chosen your music folder location yet!\nUse subcommand --set command for that')
                    return
        except:
            print('You have not chosen your music folder location yet!\n\
                            Use "path --set" command for that')
            return

        dirs = [path, ]

        if self.app.pargs.clear:
            global count_found
            count_found = 0
            with open(path + 'musrepl_db/search_list.txt', 'w') as search_file:
                pass

        deep = 1
        if self.app.pargs.deep:
            deep = int(self.app.pargs.deep)
        dirs = get_sub_dirs_deep(path, deep)

        search = ''
        if self.app.pargs.name:
            search = self.app.pargs.name

        author = self.app.pargs.author
        album = self.app.pargs.album

        search_parameters = [
            author,
            album,
        ]

        extensions = [
            'mp3',
            'wav',
            'midi',
        ]

        with open(path + 'musrepl_db/search_list.txt', 'r') as search_file:
            index = get_index(search_file)
        with open(path + 'musrepl_db/search_list.txt', 'a') as search_file:
            print('-' * 10 + 'FOUND TRACKS' + '-' * 10)
            for filedir in dirs:
                make_search(filedir, search, search_file, extensions, search_parameters, index)
            print('-' * 32)


class SearchListController(CementBaseController):
    class Meta:
        label = 'sl'
        description = 'Work with the search list (sl)'
        stacked_on = 'base'
        stacked_type = 'nested'

        arguments = [
            (['--see', '--list'],
             dict(action='store_true', help='See found tracks', dest='list')),
            (['-a', '--add'],
             dict(action='store', help='Add songs with given indexes to the playlist', dest='indexes')),
            (['--addall'],
             dict(action='store_true', help='Add all found songs to the playlist', dest='all')),
        ]

    @expose(hide=True)
    def default(self):
        if not self.app.pargs.all and not self.app.pargs.indexes and not self.app.pargs.list:
            print('Use subcommands:\n-h     Search-list settings')
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

        if self.app.pargs.list:
            with open(path + 'musrepl_db/search_list.txt', 'r') as search_file:
                if search_file.readline() == '':
                    print('You haven\'t searched tracks yet\nUse command "search"')
                else:
                    search_file.seek(0)
                    print('-' * 10 + 'SEARCH LIST' + '-' * 10)
                    for line in search_file:
                        print(line, end='')
                    print('\n' + '-' * 31)

        if self.app.pargs.all:
            with open(path + 'musrepl_db/search_list.txt', 'r') as search_file:
                if search_file.readline() == '':
                    print('You haven\'t searched tracks yet\nUse command "search"')
                else:
                    search_file.seek(0)
                    with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                        index = get_index(playlist)
                    with open(path + 'musrepl_db/playlist.txt', 'a') as playlist:
                        for line in search_file:
                            playlist.write(f'{index} {line[line.find(" "):]}')
                            if line[-1] != '\n':
                                playlist.write('\n')
                            index += 1
            return

        if self.app.pargs.indexes:
            try:
                indexes = self.app.pargs.indexes.split(',')
                i = 0
                while (i < len(indexes)):
                    if '-' in indexes[i]:
                        v = trstr(indexes[i])
                        indexes[i:i + 1] = v
                        i += len(v) - 1

                    i += 1
                indexes = list(map(int, indexes))

                with open(path + 'musrepl_db/search_list.txt', 'r') as search_file:
                    if search_file.readline() == '':
                        print('You haven\'t searched tracks yet\nUse command "search"')
                    else:
                        search_file.seek(0)
                        lines = search_file.readlines()
                        lines = list(lines[i - 1] for i in indexes)
                        with open(path + 'musrepl_db/playlist.txt', 'r') as playlist:
                            index = get_index(playlist)
                        with open(path + 'musrepl_db/playlist.txt', 'a') as playlist:
                            for line in lines:
                                playlist.write(f'{index} {line[line.find(" "):]}')
                                if line[-1] != '\n':
                                    playlist.write('\n')
                                index += 1
            except Exception as e:
                print(e)
