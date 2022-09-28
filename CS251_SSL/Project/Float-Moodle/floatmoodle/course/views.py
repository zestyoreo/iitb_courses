from django.db.models.fields import CommaSeparatedIntegerField
from django.shortcuts import render
import course
from django.contrib import messages
from course.models import Course, Feedback,User,Assignment,Submissions
from django.shortcuts import get_object_or_404, render,redirect
from .forms import CourseCreationForm,AssignmentCreationForm, FeedbackForm,StudentEnrollmentForm,AssignmentSubmissionForm
import datetime
from .serializers import CourseItemSerializer,AssignmentItemSerializer,SubmissionItemSerializer,FeedbackItemSerializer
from rest_framework.response import Response
from rest_framework.authtoken.models import Token
from rest_framework.exceptions import ParseError
from rest_framework import status
from rest_framework import parsers
from rest_framework import response
from rest_framework import viewsets
from rest_framework.authentication import TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.views import APIView

def info(request,id):
    if request.user.is_authenticated:
        course=Course.objects.get(id=id)
        instructor=User.objects.get(id=course.instructor.id)
        curr_user=request.user
        create_assign=False
        if instructor.id==curr_user.id:
            create_assign=True
        assignments=Assignment.objects.filter(course=course)
        #usrProf=get_object_or_404(Profile,user=auser)
        #repos=Repository.objects.filter(owner=usrProf).order_by('-stars')   
        #display_dateTime=usrProf.time.strftime("%b. %d, %Y, %l:%M %p")
        return render(request,'course/course_info.html',{'course':course,'assignments':assignments,'create_assignment_access':create_assign})
    else:
        return redirect('login')

def course_creation(request):
    if request.method == "POST":
        form=CourseCreationForm(request.POST)
        if form.is_valid():
            course=form.save(commit=False)
            course.instructor=request.user
            course.save()
            # print(form.cleaned_data['username'])
            # user=User.objects.get(username=form.cleaned_data['username'])
            return redirect("dashboard")      
    else:
        form=CourseCreationForm()   
    return render(request,'course/courseCreation.html',{"form":form})

def assignment_submission(request,cid,aid):
    if not request.user.is_authenticated:
        return redirect('login') 
    assign = Assignment.objects.get(id=aid)
    ifT = False
    studs = list(assign.course.studentsEnrolled.all())
    ifSu = (assign.deadline.replace(tzinfo=None) - datetime.datetime.now()) > (datetime.datetime.now()-datetime.datetime.now())
    feedl = []
    if request.user in [s.student for s in studs] or request.user==assign.course.instructor:
        for f in studs:
            if f.student==request.user and f.ifTA:
                ifT = True
        if assign.course.instructor==request.user:
            ifT = True
    else:
        return render(request,'invalid.html')
    sl = list(assign.submissions.all())
    t = 5
    for s in sl:
        if s.fromStudent==request.user:
            t = s
    if type(t)!=type(5):
        feedl = list(t.feedbacks.all())
    ifF = len(feedl)>0 
    if request.method == "POST":
        form=AssignmentSubmissionForm(request.POST,request.FILES)
        if form.is_valid:
            submission=form.save(commit=False)
            submission.timeSubmitted = datetime.datetime.now()
            submission.fromStudent = request.user
            submission.forAssign = Assignment.objects.get(id=aid)
            for x in submission.forAssign.submissions.all():
                x.delete()
            submission.save()
            

    else:
        if ifT:
            subm = assign.submissions.all()
            subl = []
            for s in subm:
                subl.append(s)
                
            return render(request,'course/assignmentFeedback.html',{'assignment':assign,'submissions':subl})
        else:
            form=AssignmentSubmissionForm()
            
            
            
    return render(request,'course/assignmentSubmission.html',{"form":form,'assignment':assign,'iFF':ifF ,'feedbacks':feedl, 'ifsubmit':ifSu})     


def feedback_submission(request,cid,aid,sid):
    print('We reached here!')
    if not request.user.is_authenticated:
        return redirect('login')
    course = Course.objects.get(id = cid) 
    ifT = False
    for s in course.studentsEnrolled.all():
        if s.student==request.user and s.ifTA:
            ifT = True
            break
    if request.user==course.instructor:
        ifT = True
    if not ifT:
        return render(request, 'invalid.html')
    subm = Submissions.objects.get(id = sid)
    feedbl = list(subm.feedbacks.all())
    if request.method=="POST":
        form = FeedbackForm(request.POST)
        if form.is_valid():
            feedb = form.save(commit = False)
            feedb.forSubmission = Submissions.objects.get(id = sid)
            feedb.save()
    else:
        form = FeedbackForm()
    return render(request,'course/GetFeedback.html',{'submission':subm,'form':form, 'feedbacks':feedbl})



def assignment_creation(request,cid):
    if not request.user.is_authenticated:
        return redirect('login') 
    cor = Course.objects.get(id = cid)
    if cor.instructor != request.user:
        return render(request,'invalid.html')
    if request.method == "POST":
        form=AssignmentCreationForm(request.POST)
        if form.is_valid():
            ass = form.save(commit = False)
            ass.ifClosed = False
            ass.course = cor
            ass.save()
            # course.instructor=request.user
            # course.save()
            # print(form.cleaned_data['username'])
            # user=User.objects.get(username=form.cleaned_data['username'])
            return redirect("dashboard")      
    else:
        form=AssignmentCreationForm()   
    return render(request,'course/assignmentCreation.html',{"form":form})

def student_enrollment(request):
    if request.method == "POST":
        form=StudentEnrollmentForm(request.POST)
        
        if form.is_valid():
            if Course.objects.get(name=form.cleaned_data['course']) in [ x.course for x in request.user.CoursesEnrolled.all()]:
                messages.info(request,'already registered')
                return redirect("course_enroll")
            if form.cleaned_data['ifTA']:
                if form.cleaned_data['code']==Course.objects.get(name=form.cleaned_data['course']).registration_code_TA:
                    student=form.save(commit=False)
                    student.student=request.user
                    student.save()
                    
                else:
                     messages.info(request,'Incorrect Registration Code. Check the code and try again')
                     return redirect("course_enroll")
            else:
                if form.cleaned_data['code']==Course.objects.get(name=form.cleaned_data['course']).registration_code_student:
                    student=form.save(commit=False)
                    student.student=request.user
                    student.save()
                else:
                     messages.info(request,'Incorrect Registration Code. Check the code and try again')
            return redirect("course_enroll")
                        


            # course.instructor=request.user
            # course.save()
            # print(form.cleaned_data['username'])
            # user=User.objects.get(username=form.cleaned_data['username'])
            return redirect("dashboard")      
    else:
        form=StudentEnrollmentForm()   
    return render(request,'course/course_enrollment.html',{"form":form})

class CourseItemViews(APIView):

    permission_classes = (IsAuthenticated,)

    def post(self, request):
        serializer = CourseItemSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)
        else:
            return Response({"status": "error", "data": serializer.errors}, status=status.HTTP_400_BAD_REQUEST)
    
    #getting info on all courses user is enrolled in
    def get(self, request, id=None):
        if id:
            item = Course.objects.get(id=id)
            serializer = CourseItemSerializer(item)
            return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)

        courses = [x.course for x in request.user.CoursesEnrolled.all()]
        items = courses + list(request.user.instructs.all())
        serializer = CourseItemSerializer(items, many=True)
        return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)

class AssignmentItemViews(APIView):

    permission_classes = (IsAuthenticated,)
    
    #getting info on all courses user is enrolled in
    def get(self, request, cid=None, aid=None):
        #view assignments in course
        if cid:
            item = Course.objects.get(id=cid)
            item = item.assignments.all()
            if aid:
                item = Assignment.objects.get(id=aid)
                serializer = AssignmentItemSerializer(item)
                return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)
            else:
                serializer = AssignmentItemSerializer(item, many=True)
                return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)

        #view all assignments there is
        courses = [x.course for x in request.user.CoursesEnrolled.all()]
        courses = courses + list(request.user.instructs.all())
        assignments = []
        for x in courses:
            assignments = assignments + list(x.assignments.all())
        items = assignments
        serializer = AssignmentItemSerializer(items, many=True)
        return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)

class SubmissionItemViews(APIView):

    permission_classes = (IsAuthenticated,)

    def post(self, request, cid=None, aid=None):
        if cid and aid:
            item = Course.objects.get(id=cid)
            item = item.assignments.all()
            assignment_to_be_submitted = Assignment.objects.get(id=aid)
            for x in assignment_to_be_submitted.submissions.all():
                x.delete()
            data = request.data.copy()
            data.__setitem__("timeSubmitted", datetime.datetime.now())
            data.__setitem__("fromStudent", request.user.id)
            data.__setitem__("forAssign", aid)
            serializer = SubmissionItemSerializer(data=data)
            print(type(data))
            print(data)
            print(serializer)
            if serializer.is_valid():
                serializer.save()
                return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)
            else:
                return Response({"status": "error", "data": serializer.errors}, status=status.HTTP_400_BAD_REQUEST)
        return Response({"status": "Fail:" "Enter the course and assignment id for which submission is to be made."}, status=status.HTTP_200_OK)
            
    
    def get(self, request, cid=None, aid=None):
        
        if aid:
            item = Assignment.objects.get(id=aid)
            serializer = AssignmentItemSerializer(item)
            return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)
        elif cid:
            item = Course.objects.get(id=cid)
            item = item.assignments.all()
            serializer = AssignmentItemSerializer(item, many=True)
            return Response({"status": "success", "data": serializer.data}, status=status.HTTP_200_OK)
        return Response({"status": "Fail:" "Enter the course and assignment id for which submission is to be made."}, status=status.HTTP_200_OK)

class FeedbackItemViews(APIView):

    permission_classes = (IsAuthenticated,)
    
    def get(self, request, aid=None):
        if aid:
            item = Feedback.objects.all()
            sub_ids = []
            for feed in item:
                if feed.forSubmission.fromStudent.id==request.user.id and feed.forSubmission.forAssign.id==aid:
                    sub_ids.append(feed)
            serializer = FeedbackItemSerializer(sub_ids,many=True)
            return Response({"status": "success","data": serializer.data }, status=status.HTTP_200_OK)
        else:
            item = Feedback.objects.all()
            sub_ids = []
            for feed in item:
                if feed.forSubmission.fromStudent.id==request.user.id:
                    sub_ids.append(feed)
            serializer = FeedbackItemSerializer(sub_ids,many=True)
            return Response({"status": "success","data": serializer.data }, status=status.HTTP_200_OK)