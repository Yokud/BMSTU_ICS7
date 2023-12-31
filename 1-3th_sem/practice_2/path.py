from cement.core.controller import CementBaseController, expose
import os

class PathController(CementBaseController):
    class Meta:
        label = 'path'
        description = 'Path settings'
        stacked_on = 'base'
        stacked_type = 'nested'

        arguments = [
            (['--set'],
             dict(action='store', help='specify the path', dest='path')),
            (['--see'],
             dict(action='store_true', help='see the current path', dest='see_path')),
        ]

    @expose(hide=True)
    def default(self):

        if not self.app.pargs.path and not self.app.pargs.see_path:
            print('Use subcommands:\n-h     Path settings\n--set  Set new path\n--see  See curent path')
            return

        if self.app.pargs.path:
            path = self.app.pargs.path
            if not os.path.exists(path):
                print('This path does not exist')
            else:
                if path[-1] != '/':
                    path += '/'

                with open('db_path.txt', 'w') as f:
                    f.write(path)
                try:
                    os.mkdir(path + 'musrepl_db')
                    with open(path + 'musrepl_db/search_list.txt', "w"):
                        pass
                    with open(path + 'musrepl_db/playlist.txt', "w"):
                        pass
                    with open(path + 'musrepl_db/playlists.txt', "w"):
                        pass

                except FileExistsError:
                    pass

        if self.app.pargs.see_path:
            try:
                with open('db_path.txt', 'r') as f:
                    path = f.readline()
                    if not path:
                        print('You have not chosen your music folder location yet!\nUse "path --set" command for that')
                    else:
                        print(f'Current path:\n{path}\n' + '-' * len(path))
            except:
                print('You have not chosen your music folder location yet!\nUse "path --set" command for that')
