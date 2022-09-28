from django.contrib import admin
from . import models
# Register your models here.

admin.site.register(models.Course)
admin.site.register(models.Assignment)
admin.site.register(models.Feedback)
admin.site.register(models.students)
admin.site.register(models.Post)
admin.site.register(models.Submissions)