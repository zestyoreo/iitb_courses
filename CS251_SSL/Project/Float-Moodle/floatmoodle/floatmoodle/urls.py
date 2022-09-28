"""floatmoodle URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from course.models import Course
from dashboard import urls
from course import urls
from django.urls import path, include
from django.urls.conf import include
from django.views.generic.base import TemplateView
from django.conf import settings
import django.conf.urls.static
from dashboard import views as dash_views
from rest_framework.authtoken.views import obtain_auth_token
from course import views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('course/', include('course.urls')),
    path('dashboard/', include('dashboard.urls')),
    path('accounts/',include('accounts.urls')),
    path('profiles/',include('profiles.urls')),
    #path('', TemplateView.as_view(template_name='moodle_login.html'), name='home'),
    path('',dash_views.explore,name='home'),

    path('api-token-auth/', obtain_auth_token, name='api_token_auth'),

    path('api/course/', views.CourseItemViews.as_view()),
    path('api/course/<int:id>/', views.CourseItemViews.as_view()),

    path('api/assignment/', views.AssignmentItemViews.as_view()),
    path('api/assignment/<int:cid>/', views.AssignmentItemViews.as_view()),
    path('api/assignment/<int:cid>/<int:aid>/', views.AssignmentItemViews.as_view()),

    path('api/submission/', views.SubmissionItemViews.as_view()),
    path('api/submission/<int:cid>/', views.SubmissionItemViews.as_view()),
    path('api/submission/<int:cid>/<int:aid>/', views.SubmissionItemViews.as_view()),

    path('api/feedback/', views.FeedbackItemViews.as_view()),
    path('api/feedback/<int:aid>/', views.FeedbackItemViews.as_view()),

]+ django.conf.urls.static.static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
