import click
import os
import subprocess
from decouple import config
from moodle.prettyprint import submission_prettyprint

@click.group()
def cli():
    """Assignment Submission"""
    pass

@cli.command()
@click.argument('aid',type=int)#assignment id
@click.argument('submission_filepath')
def upload(aid,submission_filepath):
    token = config('MOODLE_TOKEN')
    bash_command = "curl -H \"Content-Disposition: attachment;\" -H 'Authorization: Token "+str(token)+"' -X POST -F \"submission=@"+str(submission_filepath)+"\" http://127.0.0.1:8000/api/submission/1/"+str(aid)+"/"
    output = subprocess.run(bash_command,shell=True, capture_output=True,text=True)
    msg = submission_prettyprint(output.stdout)
    click.echo(msg)
    