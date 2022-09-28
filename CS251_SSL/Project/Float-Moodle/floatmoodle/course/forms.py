from django.forms import ModelForm, fields, widgets
from django.forms.models import model_to_dict
from .models import Course, Assignment, Feedback,students,Submissions
from django.contrib.admin import widgets
import django.forms

class CourseCreationForm(ModelForm):
    class Meta:
        model=Course
        #fields = '__all__'
        exclude=['instructor']

# class SubmitAssignment(ModelForm):
    
#     class Meta:
#         model = Submissions

class StudentEnrollmentForm(ModelForm):
    code=fields.CharField()
    class Meta:
        model=students
        exclude=['student']

class AssignmentSubmissionForm(ModelForm):
    class Meta:
        model = Submissions
        exclude=['forAssign','timeSubmitted','fromStudent']

class FeedbackForm(ModelForm):
    class Meta:
        model = Feedback
        exclude = ['forSubmission']

class AssignmentCreationForm(ModelForm):
    class Meta:
        model=Assignment
        fields = '__all__'
        exclude=['ifClosed','course']

    def __init__(self, *args, **kwargs):
        super(AssignmentCreationForm, self).__init__(*args, **kwargs)
        self.fields['deadline'] = django.forms.SplitDateTimeField(widget = widgets.AdminSplitDateTime())   