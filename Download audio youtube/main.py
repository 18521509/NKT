import youtube_dl
import os
import sys
def screen_clear():
   # for mac and linux(here, os.name is 'posix')
   if os.name == 'posix':
      _ = os.system('clear')
   else:
      _ = os.system('cls')

def run(step, n, video_url,audio_format , location):
    screen_clear()
    print("Downloading... {0}/{1} video".format(step+1,n))
    
    try:
        video_info = youtube_dl.YoutubeDL().extract_info(
            url = video_url,download=False
        )
        filename = os.path.join(location,f"{video_info['title']}.mp3")
        options={
            'format':'bestaudio/best',
            'keepvideo':False,
            'outtmpl':filename,
            'audioformat': audio_format,
            'ffmpeg_location': r'C:\Users\USER\Desktop\New folder\ffmpeg-4.4-full_build\bin'
        }

        with youtube_dl.YoutubeDL(options) as ydl:
            ydl.download([video_info['webpage_url']])
    except:
        pass



if __name__=='__main__':
    playlist = []
    
    audio_format = 'best'
    location = 'download'
    if len(sys.argv) == 2:
        audio_format = sys.argv[1]
        
    with open('playlist.txt') as f:
        playlist = [x for x in f]
        
    if not os.path.exists(location):
        os.makedirs(location)
       
    for step, url in enumerate(playlist):
        run(step,len(playlist), url, audio_format, location)
    screen_clear()
    print("Download complete... {0}/{0} video".format(len(playlist)))