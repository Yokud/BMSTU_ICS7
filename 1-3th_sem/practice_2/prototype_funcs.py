import click

def clear_buf():
	pass

def add_to_buf(item):
	# Add an item to buf with its' index
	pass

def clear_playlist():
	pass

def add_to_playlist_by_value(item):
	pass

def add_to_playlist_by_index(index):
	pass

def make_search(parameter):
	# Search and call add_to_buf(item) for every found item
	pass

@click.group()

def commands():
	pass

@click.command()
@click.argument("name")

def st(name):
	'''
	Search for musician's or band's tracks
	'''
	make_search(parameter=name)

@click.command()
@click.argument("indexes", nargs=-1)

def addpli(indexes):
	'''
	Add tracks with given indexes separated by spaces to playlist
	'''
	try:
		for i in indexes:
			add_to_playlist_by_index(int(i))
			click.echo("Added %s" % i)
	except ValueError:
		click.echo("Something went wrong!")

commands.add_command(st)
commands.add_command(addpli)

if __name__ == "__main__":
	commands()
	