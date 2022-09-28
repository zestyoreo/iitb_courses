from django.core.checks import messages
from django.forms import fields
from django.http import response
from django.http.response import HttpResponse
from django.shortcuts import get_object_or_404, render,redirect
from django.contrib.auth.models import User,auth
from django.contrib import messages
import requests
from requests.exceptions import HTTPError
from django.contrib.auth import get_user_model

from datetime import datetime
from django.http import HttpResponseRedirect
from django.urls import reverse
from .forms import RegisterForm

def signup(request):
    if request.method == "POST":
        form=RegisterForm(request.POST)
        if form.is_valid():
            form.save()
            # print(form.cleaned_data['username'])
            # user=User.objects.get(username=form.cleaned_data['username'])
            return redirect("/dashboard")      
    else:
        form=RegisterForm()   
    return render(request,'signup.html',{"form":form})