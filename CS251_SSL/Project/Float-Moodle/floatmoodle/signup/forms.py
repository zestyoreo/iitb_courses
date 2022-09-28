from django import forms
from django.contrib.auth import login, authenticate
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User

class RegisterForm(UserCreationForm):
    name=forms.CharField()
    roll_no=forms.CharField()

    class Meta:
        model=User
        fields = ["username","password1","password2","name","roll_no",]