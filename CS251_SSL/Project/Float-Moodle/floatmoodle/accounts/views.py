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
from .forms import RegisterForm,UserUpdateFrom

def signup(request):
    if request.method == "POST":
        form=RegisterForm(request.POST)
        if form.is_valid():
            form.save()
            # print(form.cleaned_data['username'])
            # user=User.objects.get(username=form.cleaned_data['username'])
            return redirect("login")      
    else:
        form=RegisterForm()   
    return render(request,'signup.html',{"form":form})


def login(request):
    if request.method=='POST':
        username=request.POST.get('username')
        password=request.POST.get('password')

        user=auth.authenticate(username=username,password=password)
        if user is not None:
            auth.login(request,user)
            return redirect("/dashboard/")
        else:
            messages.info(request,'invalid credentials')
            return redirect("login")
    else:
        return render(request,'moodle_login.html')

def logout(request):
    auth.logout(request)  
    return redirect('login')        


def Update(request):
    if request.method == "POST":
        form=UserUpdateFrom(request.POST,instance=request.user)
        if form.is_valid():
            form.save()
            return redirect("dashboard")      
    else:
        form=UserUpdateFrom(instance=request.user)   
    return render(request,'userupdate.html',{"form":form})  