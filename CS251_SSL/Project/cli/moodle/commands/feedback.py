import click
import os
import subprocess
from decouple import config
from moodle.prettyprint import feedback_prettyprint

@click.group()
def cli():
    """Submission Feedback"""
    pass

@cli.command()
@click.option('-aid','-a',type=int)#assignment id
def get(aid):
    token = config('MOODLE_TOKEN')
    if aid:
        bash_command = "curl -X GET http://127.0.0.1:8000/api/feedback/"+str(aid)+"/ -H 'Authorization: Token "+str(token)+"'"
    else:
        bash_command = "curl -X GET http://127.0.0.1:8000/api/feedback/ -H 'Authorization: Token "+str(token)+"'"
    output = subprocess.run(bash_command,shell=True, capture_output=True,text=True)
    msg = feedback_prettyprint(output.stdout)
    click.echo(msg)
    