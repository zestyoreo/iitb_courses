# accounts/urls.py
from django.urls import path
from django.contrib.auth import views as auth_views
from . import views


urlpatterns = [
    path('signup/', views.signup, name='signup'),
    path('login/',views.login,name='login'),
    path('reset_password/',auth_views.PasswordResetView.as_view(template_name="passwords/password_reset.html"),name="password_reset"),
    path('reset_password_sent/',auth_views.PasswordResetDoneView.as_view(template_name="passwords/password_reset_sent.html"),name="password_reset_done"),
    path('reset/<uidb64>/<token>/',auth_views.PasswordResetConfirmView.as_view(template_name="passwords/password_reset_form.html"),name="password_reset_confirm"),
    path('reset_password_complete/',auth_views.PasswordResetCompleteView.as_view(template_name="passwords/password_reset_done.html"),name="password_reset_complete"),
    path('logout/',views.logout,name='logout'),
    path('update/',views.Update,name='update')
]