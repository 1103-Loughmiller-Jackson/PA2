#!/usr/bin/python3
import subprocess
import time
import os
import sys
import glob
#insert try catches around subprocess run so that even if time out, error message is displayed
def testAdd():
    successCount = 5
    try:
        result = subprocess.run(["./jukebox"],input= "2\ntest\n1\n10\n3\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        if result.returncode != 0 or len(data) != 1 or data[0] != "Nothing Compares 2 U-Sinead O'Connor":
            print("Adding 1 song to empty playlist at creation does not work." )
            successCount -= 1
    except:
        print("Adding 1 song to empty playlist at creation does not work." )
        successCount -= 1
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n2\n1\ny\n10\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        data = [x.strip() for x in data] 
        fin.close()
        
        if result.returncode != 0 or len(data) != 1 or data[0] != "Nothing Compares 2 U-Sinead O'Connor":
            print("Program allows a song to be entered more than once." )
            successCount -= 1
    except: 
        print("Program allows a song to be entered more than once." )
        successCount -= 1
    #find a better way to ensure order, list of strings? check if a is followed by b in list
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n2\n7\ny\n10\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        data = [x.strip() for x in data]
        if result.returncode != 0 or data[0] != "Nothing Compares 2 U-Sinead O'Connor" or data[1] != "Papa Was a Rollin' Stone-The Temptations":
            print("Program does not successfully add song to end when one song is in list")
            successCount -= 1
    except:
        print("Program does not successfully add song to end when one song is in list")
        successCount -= 1

    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n2\n3\nn\n1\n10\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        data = [x.strip() for x in data]
        if result.returncode != 0 or len(data) != 3 or data[0] != "Folsom Prison Blues-Johnny Cash" or data[1] != "Nothing Compares 2 U-Sinead O'Connor":
            print("Program does not successfully add song to front when one song is in list")
            successCount -= 1
    except:
        print("Program does not successfully add song to front when one song is in list")
        successCount -= 1
    return successCount * 2
def testDelete():
    successCount = 1
    f = open("test.txt", "w")
    f.write("Nothing Compares 2 U-Sinead O'Connor")
    f.close()
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n2\n2\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        if result.returncode != 0 or os.path.exists("test.txt"):
            print("Choosing to delete playlist does not work." )
            successCount -= 1
    except:
        print("Choosing to delete playlist does not work." )
        successCount -= 1
    return successCount * 4

def testRemove():
    successCount = 5
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n1\n1\n4\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        data = [x.strip() for x in data]
        if result.returncode != 0 or len(data) != 2 or data[0] != "Nothing Compares 2 U-Sinead O'Connor" or data[1] != "Papa Was a Rollin' Stone-The Temptations":
            print("Removing first song from playlist does not work." )
            successCount -= 1
    except:
        print("Removing first song from playlist does not work." )
        successCount -= 1
    f = open("test.txt", "w")
    f.write("Folsom Prison Blues-Johnny Cash\nFast Car-Tracy Chapman\nLose Yourself-Eminem\nLet's Get It On-Marvin Gaye\nPapa Was a Rollin' Stone-The Temptations\nLosing My Religion-R.E.M.\nBoth Sides Now-Joni Mitchell")
    f.close()
    f = open("test.txt", "w")
    f.write("Folsom Prison Blues-Johnny Cash\nFast Car-Tracy Chapman\nLose Yourself-Eminem\nLet's Get It On-Marvin Gaye\nPapa Was a Rollin' Stone-The Temptations\nLosing My Religion-R.E.M.\nBoth Sides Now-Joni Mitchell")
    f.close()
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n1\n7\n8\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        data = [x.strip() for x in data]
        if result.returncode != 0 or len(data) != 6 or data[0] != "Folsom Prison Blues-Johnny Cash" or data[1]!= "Fast Car-Tracy Chapman" or data[2] != "Lose Yourself-Eminem" or data[3]!= "Let's Get It On-Marvin Gaye" or data[4] != "Papa Was a Rollin' Stone-The Temptations" or data[5] != "Losing My Religion-R.E.M.":
            print("Removing song from end does not work." )
            successCount -= 1
    except:
        print("Removing song from end does not work." )
        successCount -= 1
    f = open("test.txt", "w")
    f.write("Folsom Prison Blues-Johnny Cash\nFast Car-Tracy Chapman\nLose Yourself-Eminem\nLet's Get It On-Marvin Gaye\nPapa Was a Rollin' Stone-The Temptations\nLosing My Religion-R.E.M.\nBoth Sides Now-Joni Mitchell")
    f.close()
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n1\n4\n1\n7\n8\n4\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        fin = open("test.txt", "r")
        data = fin.readlines()
        fin.close()
        data = [x.strip() for x in data]
        if result.returncode != 0 or len(data) != 4 or data[0] != "Fast Car-Tracy Chapman" or data[1] != "Lose Yourself-Eminem" or data[2] != "Papa Was a Rollin' Stone-The Temptations" or data[3] != "Losing My Religion-R.E.M.":
            print("Removing multiple songs in random order (4, 1, 7) does not work." )
            successCount -= 1
    except:
        print("Removing multiple songs in random order (4, 1, 7) does not work." )
        successCount -= 1
    f = open("test.txt", "w")
    f.write("Both Sides Now-Joni Mitchell")
    f.close()
    try:
        result = subprocess.run(["./jukebox"],input= "1\n1\n1\n1\n1\ny\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
        if os.path.exists("test.txt"):
            print("Removing last song from playlist does not delete playlist." )
            successCount -= 1
    except:
        print("Removing last song from playlist does not delete playlist." )
        successCount -= 1
    if os.path.exists("test.txt"):
        os.remove("test.txt")
    return successCount *2
    


        

def testExits():
    success = prepEnv()
    successCount = 0
    if success:
        successCount = 13
        
        try:
            result = subprocess.run(["./jukebox"],input= "3\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit at main screen")
                successCount -= 1
        except:
            print("Program does not exit at main screen")
            successCount -= 1
        
        try:
            result = subprocess.run(["./jukebox"],input= "1\n2\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("b, Program does not exit at existing playlist selection menu.")
                successCount -= 1
        except:
            print("B, Program does not exit at existing playlist selection menu.")
            successCount -= 1
        try:
            result = subprocess.run(["./jukebox"],input= "1\n1\n3\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to load, choosing to return to main, and then choosing to exit.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to load, choosing to return to main, and then choosing to exit.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"],input= "2\ntest\n11\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, and then choosing to exit the program.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, and then choosing to exit the program.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"],input= "2\ntest\n10\n3\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, choosing to finalize, and then choosing to exit from main menu.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, choosing to finalize, and then choosing to exit from main menu.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"],input= "2\ntest\n1\n11\ny\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            os.remove("test.txt")
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, selecting a song, choosing to exit, and choosing to save choices.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, selecting a song, choosing to exit, and choosing to save choices.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"],input= "2\ntest\n1\n11\nn\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, selecting a song, choosing to exit, and choosing not to save.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, selecting a song, choosing to exit, and choosing not to save.")
            successCount -= 1
        #time.sleep(1)
        try:
            #os.remove("test.txt")
            result = subprocess.run(["./jukebox"],input= "2\ntest\n11\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, and then choosing to exit the program.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, and then choosing to exit the program.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"],input= "2\ntest\n1\n10\n3\n", encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to create new playlist, giving a name, adding a song, choosing to finalize, and then selecting exit from main menu")
                successCount -= 1
        except:
            print("Program does not exit after choosing to create new playlist, giving a name, adding a song, choosing to finalize, and then selecting exit from main menu")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"], input = "1\n1\n4\n",  encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to open existing playlist and then choosing to exit.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to open existing playlist and then choosing to exit.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"], input = "1\n1\n1\n4\n",  encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to open existing playlist, choosing to modify playlist, and then choosing to exit.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to open existing playlist, choosing to modify playlist, and then choosing to exit.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"], input = "1\n1\n1\n1\n3\n",  encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to open existing playlist, choosing to modify playlist, choosing to remove a song, and then choosing to exit.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to open existing playlist, choosing to modify playlist, choosing to remove a song, and then choosing to exit.")
            successCount -= 1
        #time.sleep(1)
        try:
            result = subprocess.run(["./jukebox"], input = "1\n1\n2\n2\n",  encoding = "utf-8",capture_output=True, text=True, timeout=60)
            if result.returncode != 0:
                print("Program does not exit after choosing to open existing playlist, choosing to delete playlist, and then choosing to exit.")
                successCount -= 1
        except:
            print("Program does not exit after choosing to open existing playlist, choosing to delete playlist, and then choosing to exit.")
            successCount -= 1
    
    return successCount * 2

def constructTxt():
    f = open("dbLarge.txt", "w")
    f.write("Nothing Compares 2 U-Sinead O'Connor\nBohemian Rhapsody-Queen\nFolsom Prison Blues-Johnny Cash\nFast Car-Tracy Chapman\nLose Yourself-Eminem\nLet's Get It On-Marvin Gaye\nPapa Was a Rollin' Stone-The Temptations\nLosing My Religion-R.E.M.\nBoth Sides Now-Joni Mitchell")
    f.close()

def prepEnv():
    for file in glob.glob("*.txt"): #remove all txt files that aren't the db
        if file != "dbSmall.txt":
            os.rename(file, file[:-4]+"_o")
    if os.path.exists("./jukebox"):
        os.remove("jukebox")
    constructTxt()
    makeResult = subprocess.call(['make'], stdout=subprocess.DEVNULL)
    cleanResult = subprocess.call(['make', 'clean'], stdout=subprocess.DEVNULL)
    if cleanResult != 0 :
        print("Clean command missing from makefile")

    makeResult = subprocess.call(['make'], stdout=subprocess.DEVNULL)
    if makeResult != 0:
        print("Unable to make. Did you include your makefile?")
    return makeResult == cleanResult

totalScore = 0
totalScore += testExits()
totalScore += testDelete()
totalScore += testAdd()
totalScore += testRemove()
print("\nPlease note that if you are getting timeout errors, you probably hardcoded the number for exit or return to main;\ninstead, use the number of songs in the playlist + 1 (or 2) to do that.\n")
print("If you failed any of the exit tests, they can cause the delete, add, and remove tests to fail since we rely on proper program termination to check for values.\nFix the exits first and rerun the test before  making changes to get other tests to pass.\n")
print("Final test score: " + str(totalScore) + "/50\n")
os.remove("dbLarge.txt") #remove the constructed txt
for file in glob.glob("*_o"): #rename old playlists so they reappear
    os.rename(file, file[:-2]+".txt")
