from django.db import models
from django.contrib.auth.models import User
from ckeditor.fields import RichTextField 

# Create your models here.


class Course(models.Model):
    name=models.CharField(max_length=50)
    description=RichTextField()
    registration_code_student=models.CharField(max_length=10)
    registration_code_TA=models.CharField(max_length=10)
    instructor=models.ForeignKey(User,related_name = 'instructs',on_delete=models.CASCADE)#Many instructors or one?
    numberOfAssignments =  models.FloatField(default=0)
    TA_can_create_Assignment = models.BooleanField(default=False)
    TA_can_make_Announcement = models.BooleanField(default=False)
    TA_can_turn_disscussion_forum_off=models.BooleanField(default=False)
    discussion_forum_on=models.BooleanField(default=False)

    def __str__(self) -> str:
        return self.name

class students(models.Model):
    course = models.ForeignKey(Course,related_name = 'studentsEnrolled',on_delete=models.CASCADE)
    student = models.ForeignKey(User,related_name = 'CoursesEnrolled',on_delete=models.CASCADE)
    ifTA = models.BooleanField()
    score = models.FloatField(default=0)
    numberCompleted = models.FloatField(default=0)


    def __str__(self) -> str:
        return self.student.username

class Post(models.Model):
    name = models.CharField(max_length = 50)
    course = models.ForeignKey(Course,related_name = 'posts',on_delete=models.CASCADE)
    description = RichTextField()
    ifDone = models.BooleanField()
    
    def __str__(self) -> str:
        return self.name

class Assignment(models.Model):
    name=models.CharField(max_length=50)
    course=models.ForeignKey(Course,related_name='assignments',on_delete=models.CASCADE)
    deadline = models.DateTimeField()
    description = RichTextField()
    if_Closed = models.BooleanField()
    if_Graded = models.BooleanField(default=False)
    totalMarks = models.FloatField()
    percentageTowardsCourseTotal = models.FloatField()
    if_Autograde_On_Submission = models.BooleanField(default=False)
    grader=models.FileField(upload_to="grad/",null=True,blank=True)

    def __str__(self) -> str:
        return self.name


class Submissions(models.Model):
    forAssign = models.ForeignKey(Assignment,related_name='submissions',on_delete=models.CASCADE)
    fromStudent = models.ForeignKey(User,related_name = 'submissions',on_delete=models.CASCADE)
    fromstudent = models.ForeignKey(students, related_name='submissions',on_delete=models.CASCADE)
    timeSubmitted = models.DateTimeField()
    score = models.FloatField(default = 0)
    submission = models.FileField(upload_to="abc/")

    def __str__(self) -> str:
        return self.fromStudent.username

class Feedback(models.Model):
    forSubmission = models.ForeignKey(Submissions,related_name = 'feedbacks',on_delete=models.CASCADE)
    ifAdditive = models.BooleanField(default=False)
    ifFinal = models.BooleanField(default=False)
    feedback = models.CharField(max_length = 500)
    marks = models.FloatField()
