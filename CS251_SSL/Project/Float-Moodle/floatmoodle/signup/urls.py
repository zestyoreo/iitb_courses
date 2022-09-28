# accounts/urls.py
from django.urls import path

from . import views


urlpatterns = [
    path('', views.signup, name='signup'),
]