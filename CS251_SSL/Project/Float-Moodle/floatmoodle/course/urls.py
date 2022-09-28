from django.urls import path
from django.conf import settings
import django.conf.urls.static
from . import views

# Create your views here.

urlpatterns=[
    # ex : /dashboard/
    path('<int:id>/',views.info,name='courses'),
    path('courseCreation/',views.course_creation,name="courseCreation"),
    path('<int:cid>/assignmentCreation/',views.assignment_creation,name="assignmentCreation"),
    path('courseEnrollment/',views.student_enrollment,name="course_enroll"),
    path('<int:cid>/<int:aid>/',views.assignment_submission,name="assignment_submission"),
    path('<int:cid>/<int:aid>/<int:sid>/',views.feedback_submission,name="feedbackSubmission"),
]+ django.conf.urls.static.static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)