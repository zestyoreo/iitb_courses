from django import forms
from django.contrib.auth import login, authenticate
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User

class RegisterForm(UserCreationForm):
    first_name=forms.CharField()
    roll_no=forms.CharField()
    email=forms.EmailField()

    class Meta:
        model=User
        fields = ["username","password1","password2","first_name","roll_no","email"]

class UserUpdateFrom(forms.ModelForm):
    email=forms.EmailField()

    class Meta:
        model=User
        fields=['username','email']        