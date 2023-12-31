
from cement.core import foundation
import glob, os

app = foundation.CementApp('test')
path = '' ### music folder path

app.setup()

app.args.add_argument('--set-path', action='store', dest='path',
					  help='set path for the folder with music')

app.args.add_argument('--see-path', action='store_true', dest='see_path',
					  help='see the current music folder path')

app.args.add_argument('-a', '--add', action='store', dest='indexes',
					  help='add tracks with given indexes to the playlist')

app.args.add_argument('-s', '--search', action='store_true', dest='search',
					  help='search #todo#') ### todo

app.run()

def trstr(x):
	"""Transform string x by the rule: '2-5' => ['2', '3', '4', '5'];
									   '5-2' => ['5', '4', '3', '2']."""
	a = int(x[:x.index('-')])
	b = int(x[x.index('-') + 1:])

	if a > b:
		b -= 1
		step = -1
	else:
		b += 1
		step = 1

	return list(map(str, list(range(a, b, step))))

def create_playlist():
	pass

if app.pargs.path:

	path = app.pargs.path
	if not os.path.exists(path):
		print('This path does not exist')
	else:
		with open('db_path.txt', 'w') as f:
			f.write(path)


with open('db_path.txt', 'r') as f:
	path = f.readline()
	if not path:
		print('You have not chosen your music folder location yet!\n\
Use --set-path command for that')

found = path + '/musrepl_db/found.txt'
playlist = path + '/musrepl_db/playlist.txt'
playlists = path + '/musrepl_db/playlists.txt'

if path:

	if app.pargs.see_path:
		print(f'Current path:\n{path}\n' + '-'*len(path))

	if app.pargs.indexes:
		
		indexes = app.pargs.indexes.split(',')
		i = 0
		while (i < len(indexes)):
			if '-' in indexes[i]:
				try:
					v = trstr(indexes[i])
					indexes[i:i+1] = v
					i += len(v) - 1
				except ValueError:
					print('Check if you typed more, than one \'-\' between numbers')
					break
			
			i += 1

		try:
			os.mkdir(path + '/musrepl_db')
		except FileExistsError:
			pass

		# try:
		# 	with open(found, 'r') as src, open(playlist, 'a') as dst:
		# 		pass
		# except IndexError:
		# 	print('Can\'t find tracks with some of the given index values')

	if app.pargs.search:

		for file in (glob.glob(path + '/*')):
			print(file)

app.close()
