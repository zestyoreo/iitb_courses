import click
import os
import subprocess
from decouple import config
from moodle.prettyprint import course_prettyprint

@click.group()
def cli():
    """Course Info"""
    pass

@cli.command()
@click.option('--course_id','-c',type=int,help="id of course you need details of.")
def info(course_id=None):
    isID = False
    token = config('MOODLE_TOKEN')
    bash_command = "curl -X GET http://127.0.0.1:8000/api/course/" 
    if course_id!=None:
        bash_command=bash_command+str(course_id)+"/"
        isID=True
    bash_command=bash_command+" -H 'Authorization: Token "+str(token)+"'"
    output = subprocess.run(bash_command,shell=True, capture_output=True,text=True)
    msg = course_prettyprint(output.stdout,isID)
    click.echo(msg)
    