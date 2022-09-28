import click
import os
import subprocess
from decouple import config

@click.group()
def cli():
    """All things SignIn!"""
    pass

@cli.command()
@click.argument('username')
@click.option('--show_token','-s',is_flag=True,help="Show Token of your account.")
@click.password_option()
def log(username,password,show_token):
    bash_command = "curl -X POST http://127.0.0.1:8000/api-token-auth/ -d \"username="+username+"&password="+password+"\""
    output = subprocess.run(bash_command,shell=True, capture_output=True,text = True)
    token_split = output.stdout.split("\"") 
    token = token_split[3]
    if show_token:
        click.echo(token)
    MOODLE_TOKEN = token
    API_USER = username
    API_PASSWORD = password
    MOODLE_TOKEN = "MOODLE_TOKEN="+token+"\n"
    API_USER = "API_USER="+username+"\n"
    API_PASSWORD = "API_PASSWORD="+password
    subprocess.run("touch .env",shell=True)
    env_file = open(".env", "w")
    env_file.write(MOODLE_TOKEN)
    env_file.write(API_USER)
    env_file.write(API_PASSWORD)
    env_file.close()
    click.echo("Successfully Logged In!")


@cli.command()
@click.option('--show_password','-s',is_flag=True,help="Show Password of your account.")
def account(show_password):
    tok_key = config('MOODLE_TOKEN')
    USER = config('API_USER')
    tok_key = "TOKEN: "+str(tok_key)
    USER = "USERNAME: "+str(USER)
    click.echo(tok_key)
    click.echo(USER)
    if show_password:
        PASSWORD = config('API_PASSWORD')
        PASSWORD = "PASSWORD: "+str(PASSWORD)
        click.echo(PASSWORD)