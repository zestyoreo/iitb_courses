from django.shortcuts import render
from course.models import Course,User,Assignment
from django.shortcuts import get_object_or_404, render,redirect

def explore(request):
    if request.user.is_authenticated:
        courses = [x.course for x in request.user.CoursesEnrolled.all()]
        courses = courses + list(request.user.instructs.all())
        users=User.objects.all()
        assignments = []
        for x in courses:
            assignments = assignments + list(x.assignments.all())
        mysub = request.user.submissions.all()
        for s in mysub:
            
            for i in range(0,len(assignments)):
                if s.forAssign==assignments[i]:
                    del assignments[i]
                    break
        
        
        #dict={'courses':courses,'users':users}
        #data=user.objects.all().exclude(is_superuser=True)
        return render(request,'dashboard3.html',{'courses':courses,'users':users,'assignments':assignments})
    else:
        return redirect('login')    