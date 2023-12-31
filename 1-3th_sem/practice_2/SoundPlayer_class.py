import pyaudio
from pydub import AudioSegment
from pydub.utils import make_chunks
import threading


class SoundPlayer:
    IN_SEC = 1000.0

    def __init__(self, soundfile):
        self.soundfile = soundfile
        self.isplaying = False
        self.time = 0
        self.audio = pyaudio.PyAudio()
        self.pydubfile = None
        self.volume = 100
        self.isended = False
        self.thread = None
        self.islooped = False

        try:
            self.pydubfile = AudioSegment.from_file(self.soundfile)
            self.isvalid = True
        except:
            self.isvalid = False

    def IsValid(self):
        return self.isvalid

    def Duration(self):
        return self.pydubfile.duration_seconds

    def IsPlaying(self):
        return self.isplaying

    def IsEnded(self):
        return self.isended

    def SetCurTime(self, time):
        if time <= int(self.pydubfile.duration_seconds):
            self.time = time
            if self.isplaying:
                self.PlaySegment(self.CurrentTime(), self.Duration())

    def Pause(self):
        self.isplaying = False

    def Start(self):
        self.PlaySegment(self.CurrentTime(), self.Duration())

    def CurrentTime(self):
        return self.time

    def SetVolume(self, volume):
        if volume <= 100 and volume:
            self.volume = volume
            if self.isplaying:
                self.PlaySegment(self.CurrentTime(), self.Duration())

    def GetVolume(self):
        return self.volume

    def Loop(self):
        self.islooped = True

    def IsLooped(self):
        return self.islooped

    def LoopOff(self):
        self.islooped = False

    def Stop(self):
        self.isended = True

    def _play(self, start, length):
        self.isplaying = True
        millisecondchunk = 50 / self.IN_SEC

        stream = self.audio.open(format=self.audio.get_format_from_width(self.pydubfile.sample_width), channels=self.pydubfile.channels,
                                 rate=self.pydubfile.frame_rate, output=True)

        playchunk = self.pydubfile[start*self.IN_SEC:(start+length)*self.IN_SEC] - (60 - (60 * (self.volume/100.0)))
        self.time = start
        for chunks in make_chunks(playchunk, millisecondchunk*int(self.IN_SEC)):
            self.time += millisecondchunk
            stream.write(chunks._data)
            if not self.isplaying or self.isended:
                break
            if self.time >= int(self.pydubfile.duration_seconds):
                self.isended = True
                break

        self.isplaying = False
        stream.close()

        if self.IsEnded() and self.IsLooped():
            self.Play()

    def Play(self):
        if self.thread is not None and self.thread.is_alive():
            self.thread.join()
        self.thread = threading.Thread(target=self._play, args=(0, self.Duration()))
        self.thread.start()

    def PlaySegment(self, start, length):
        self.isplaying = False
        if self.thread is not None and self.thread.is_alive():
            self.thread.join()
        self.thread = threading.Thread(target=self._play, args=(start, length))
        self.thread.start()
