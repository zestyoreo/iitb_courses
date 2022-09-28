import click
import os
import subprocess
from decouple import config
from moodle.prettyprint import assignment_prettyprint

@click.group()
def cli():
    """Assignment Info"""
    pass

@cli.command()
@click.option('--course_id','-c',type=int,help="id of course whose assignments you need info.")
@click.option('--assignment_id','-a',type=int,help="id of assignment you need info.")
def info(assignment_id=None,course_id=None):
    token = config('MOODLE_TOKEN')
    bash_command = "curl -X GET http://127.0.0.1:8000/api/assignment/" 
    if course_id!=None:
        bash_command=bash_command+str(course_id)+"/"
        if assignment_id!=None:
            bash_command=bash_command+str(assignment_id)+"/"
    elif assignment_id!=None:
        bash_command=bash_command+"1/"+str(assignment_id)+"/"
    bash_command=bash_command+" -H 'Authorization: Token "+str(token)+"'"
    output = subprocess.run(bash_command,shell=True, capture_output=True,text=True)
    isAID = assignment_id!=None
    msg = assignment_prettyprint(output.stdout,isAID)
    click.echo(msg)
    