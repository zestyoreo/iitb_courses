from django.urls import path
from . import views

# Create your views here.

urlpatterns=[
    # ex : /dashboard/
    path('',views.explore,name='dashboard'),

    
]