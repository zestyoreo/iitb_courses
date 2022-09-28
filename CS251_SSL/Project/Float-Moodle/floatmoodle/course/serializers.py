from rest_framework import serializers
from ckeditor.fields import RichTextField 
from course.models import Course,User,Assignment,Submissions,Feedback

class CourseItemSerializer(serializers.ModelSerializer):
    name=serializers.CharField(max_length=50)
    description=RichTextField()
    registration_code_student=serializers.CharField(max_length=10)
    class Meta:
        model = Course
        fields = ('id','name','description','instructor','registration_code_student')

class AssignmentItemSerializer(serializers.ModelSerializer):
    name=serializers.CharField(max_length=50)
    deadline = serializers.DateTimeField()
    description = RichTextField()
    ifClosed = serializers.BooleanField()
    totalMarks = serializers.FloatField()
    percentageTowardsCourseTotal = serializers.FloatField()
    class Meta:
        model = Assignment
        fields = ('__all__')

class SubmissionItemSerializer(serializers.ModelSerializer):
    submission = serializers.FileField()
    class Meta:
        model = Submissions
        fields = ('__all__')

class FeedbackItemSerializer(serializers.ModelSerializer):
    feedback = serializers.CharField(max_length = 500)
    marks = serializers.FloatField()
    class Meta:
        model = Feedback
        fields = ('__all__')