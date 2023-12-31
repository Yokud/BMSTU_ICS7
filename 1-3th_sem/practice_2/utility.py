import glob
import eyed3

def compare_parameters(audiofile, search_parameters):

    if search_parameters == [None, None]:
        return 1

    audio_parameters = [
        audiofile.tag.artist,
        audiofile.tag.album,
    ]

    for i, p in enumerate(search_parameters):
        if p != None and audio_parameters[i] != search_parameters[i]:
            return 0
    return 1

def make_search(path, search, search_file, extensions, parameters, index):

    for ext in extensions:
        for track in glob.glob(f'{path}*{search}*.{ext}'):
            if compare_parameters(eyed3.load(track), parameters):
                search_file.write(f'{index} {track[len(path):]}\n')
                print(f'{index} {track[len(path):]}\n')

                index += 1

    return index


def get_sub_dirs(path):
    dirs = []
    for dir in glob.glob(path + '*/'):
        dirs.append(dir)
    return dirs


def get_sub_dirs_deep(path, depth):
    dirs = [path, ]
    cur = [path, ]
    found = []

    for i in range(depth - 1):
        for dir in cur:
            found += get_sub_dirs(dir)
        dirs.extend(found)
        cur = found[:]
        found = []

    return dirs


def get_index(file):
    """Get index of the next track from file"""

    index = ''
    for line in file:
        index = ''
        for i in line:
            if i not in ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0']:
                break
            index += i
    if index == '':
        return 1
    else:
        return int(index) + 1

def trstr(x):
    """Transform string x by the rule: '2-5' => [2, 3, 4, 5];
                                       '5-2' => [5, 4, 3, 2]."""
    a = int(x[:x.index('-')])
    b = int(x[x.index('-') + 1:])

    if a > b:
        b -= 1
        step = -1
    else:
        b += 1
        step = 1

    return list(range(a, b, step))
