import os
#getting the words
with open('texttobespoken.txt') as f:
    words = f.readlines()
    words = words[0].split()
num_words = len(words)

#getting instances of utterance of each word in the list
n=0
word_speaker_list_of_sets = []
for w in words:
    n+=1
    os.system('grep {} ../exp/tri1/ctm > instances{}.txt'.format(w,n))

    #finding speakers and making list of all speakers who spoke w and saving in a set
    filename = "instances"+str(n)+".txt"
    speakers = []

    f = open(filename,"r")
    lines_raw = f.readlines()
    lines = [x.strip().split() for x in lines_raw]
    for x in lines:
        speaker = x[0][4:6]
        speakers.append(speaker)
    f.close()
    word_speaker_list_of_sets.append(set(speakers))

#finding intersection of all the speakers who have uttered each word to get atleast one speaker who has uttered it
all_words_one_speaker = word_speaker_list_of_sets[0]
for s in word_speaker_list_of_sets:
    all_words_one_speaker = all_words_one_speaker.intersection(s)

#speaker from which all audio clips will be taken
speaker = list(all_words_one_speaker)[0]

os.system('mkdir clips')
#getting the clips
for i in range(num_words): #each word we search each instance file
    speaker_string = "_"+speaker+"_"
    os.system('grep {} instances{}.txt > instances_word_{}_speaker_{}.txt'.format(speaker_string,str(i+1),str(i+1),speaker))
    
    filename = "instances_word_"+str(i+1)+"_speaker_"+speaker+".txt"
    with open(filename) as f:
        l= f.readlines()
        lines = [x.strip().split() for x in l]
        for x in lines:
            os.system('sox ../wav/{}.wav clips/word{}.wav trim {} {}'.format(x[0][:15],str(i+1),x[2],x[3]))
            break

os.system('sox clips/*.wav output.wav')