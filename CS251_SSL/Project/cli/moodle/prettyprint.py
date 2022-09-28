
def course_prettyprint(output,isID):
    msg = ""
    token_split = output.split("\"") 
    delim = ""
    token_split = delim.join(token_split)
    #all courses case
    if not isID:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            token_split = token_split.split("[")[1]
            token_split = token_split.split("]")[0]
            token_split = token_split.split("},")
            num_c = 1
            for c in token_split:
                c = c.split("{")[1]
                c = c.split("}")[0]
                c = c.split(",")
                msg = msg+"\n\t\tCOURSE "+str(num_c)+"\n"
                num_c+=1
                for att in c:
                    attribute = att.split(":")[0]
                    value = att.split(":")[1]
                    msg = msg+attribute.upper()+": "+value+"\n"
    #single couse case (with course-id)
    else:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            c = token_split.split("{")[2]
            c = c.split("}")[0]
            c = c.split(",")
            msg = msg+"\n\t\tCOURSE\n"
            for att in c:
                attribute = att.split(":")[0]
                value = att.split(":")[1]
                msg = msg+attribute.upper()+": "+value+"\n"

    return msg

def assignment_prettyprint(output,isAID):
    msg = ""
    token_split = output.split("\"") 
    delim = ""
    token_split = delim.join(token_split)
    #all assignments/all course assignments case
    if not isAID:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            token_split = token_split.split("[")[1]
            token_split = token_split.split("]")[0]
            token_split = token_split.split("},")
            num_c = 1
            for c in token_split:
                c = c.split("{")[1]
                c = c.split("}")[0]
                c = c.split(",")
                msg = msg+"\n\t\tASSIGNMENT "+str(num_c)+"\n"
                num_c+=1
                for att in c:
                    attribute = att.split(":")[0]
                    value = att.split(":")[1]
                    msg = msg+attribute.upper()+": "+value+"\n"
    #single couse case (with course-id)
    else:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            c = token_split.split("{")[2]
            c = c.split("}")[0]
            c = c.split(",")
            msg = msg+"\n\t\tASSIGNMENT\n"
            for att in c:
                attribute = att.split(":")[0]
                value = att.split(":")[1]
                msg = msg+attribute.upper()+": "+value+"\n"

    return msg

def submission_prettyprint(output):
    msg = ""
    token_split = output.split("\"") 
    delim = ""
    token_split = delim.join(token_split)
    #all assignments/all course assignments case
    if True:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            c = token_split.split("{")[2]
            c = c.split("}")[0]
            c = c.split(",")
            msg = msg+"\n\t\tASSIGNMENT\n"
            for att in c:
                attribute = att.split(":")[0]
                if attribute=="id":
                    attribute = "submission id"
                value = att.split(":")[1]
                msg = msg+attribute.upper()+": "+value+"\n"
    return msg

def feedback_prettyprint(output):
    msg = ""
    token_split = output.split("\"") 
    delim = ""
    token_split = delim.join(token_split)
    #all assignments/all course assignments case
    if True:
        status = token_split.split(":")[1]
        status = status.split(",")[0]
        msg = msg+"STATUS: "+status
        if status!="success":
            return msg
        else:
            token_split = token_split.split("[")[1]
            token_split = token_split.split("]")[0]
            token_split = token_split.split("},")
            num_c = 1
            for c in token_split:
                if c=="":
                    msg = msg+" No feedbacks given!"
                    return msg
                c = c.split("{")[1]
                c = c.split("}")[0]
                c = c.split(",")
                msg = msg+"\n\t\tASSIGNMENT "+str(num_c)+"\n"
                num_c+=1
                for att in c:
                    attribute = att.split(":")[0]
                    if attribute=="id":
                        attribute = "Feedback id"
                    if attribute=="forSubmission":
                        attribute = "Submission id"
                    value = att.split(":")[1]
                    msg = msg+attribute.upper()+": "+value+"\n"
    return msg