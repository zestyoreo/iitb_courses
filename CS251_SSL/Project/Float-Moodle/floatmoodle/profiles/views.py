from django.shortcuts import render
from course.models import Course,User
from django.shortcuts import get_object_or_404, render,redirect

def profile(request,id):
    if request.user.is_authenticated:
        auser=User.objects.get(id=id)
        courses = [x.course for x in auser.CoursesEnrolled.all()]
        #usrProf=get_object_or_404(Profile,user=auser)
        #repos=Repository.objects.filter(owner=usrProf).order_by('-stars')   
        #display_dateTime=usrProf.time.strftime("%b. %d, %Y, %l:%M %p")
        return render(request,'profile.html',{'auser':auser,'courses':courses})
    else:
        return redirect('login')