from cement.core.foundation import CementApp
from cement.core.controller import CementBaseController
from path import PathController
from search import SearchController, SearchOptions, SearchListController
from playlists import PlaylistsController
from play import MusicPlayerController

class BaseAppController(CementBaseController):
    class Meta:
        label = 'base'
        description = 'MusREPL'


class App(CementApp):
    class Meta:
        label = 'MusREPL'
        handlers = [
            BaseAppController,
            PathController,
            SearchController,
            SearchOptions,
            SearchListController,
            PlaylistsController,
            MusicPlayerController
        ]


def main():
    with App() as app:
        app.run()


if __name__ == '__main__':
    main()
