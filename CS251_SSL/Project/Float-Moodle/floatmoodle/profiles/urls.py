from django.urls import path
from . import views

# Create your views here.

urlpatterns=[
    # ex : /profile/id
    path('<int:id>/',views.profile,name='profile'),  
]