import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash

app = Flask(__name__)
app.config.from_object(__name__)


app.config.update(dict(
    DATABASE = os.path.join(app.root_path, 'flaskr.db'),
    SECRET_KEY = os.environ.get('SECRET_KEY', 'abrakadabra'),
    USERNAME = 'admin',
    PASSWORD = os.environ.get('PASSWORD', 'default')
))

app.config.from_envvar('FLASKR_SETTINGS', silent=True)

def connect_db():
    '''Connects to the specific database '''
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory =sqlite3.Row
    return rv

def get_db():
    '''Opens a new db connection if none is defined on the app context '''
    if (not hasattr(g, 'sqlite_db')):
        setattr(g, 'sqlite_db', connect_db())
    return g.sqlite_db

def init_db():
    db = get_db()
    with app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()

@app.cli.command('initdb')
def initdb_command():
    init_db()
    print('Database successfully initialized')

@app.teardown_appcontext
def close_db(error):
    '''closes connection.'''
    if (hasattr(g, 'sqlite_db')):
        g.sqlite_db.close()

@app.route('/')
def show_entries():
    db = get_db()
    cur = db.execute('SELECT title, text FROM entries;')
    return render_template('show_entries.html', entries = cur.fetchall())

@app.route('/add', methods = ['POST'])
def add_entry():
    if (not session.get('logged_in')):
        abort(404)
    db = get_db()
    db.execute('INSERT INTO entries (title, text) values (?, ?)', [request.form['title'], request.form['text']])
    db.commit()
    flash('New entry was successfully made!')
    return redirect(url_for('show_entries'))

@app.route('/login', methods = ['GET', 'POST'])
def login():
    error = None
    if (request.method == 'POST'):
        if request.form['username'] != app.config['USERNAME']:
            error = 'Invalid username!'
        elif request.form['password'] != app.config['PASSWORD']:
            error = 'Invalid password!'
        else:
            session['logged_in'] = True
            flash('You are logged in...')
            return redirect(url_for('show_entries'))
    return render_template('login.html', error = error)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were logged out')
    return redirect(url_for('show_entries'))



