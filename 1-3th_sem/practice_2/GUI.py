from tkinter import *
from PIL import ImageTk, Image
from SoundPlayer_class import *


class GUI:

    def __init__(self, parent, Playlist, num_of_track):
        self.parent = parent
        self.num_track = num_of_track
        self.Playlist = Playlist
        self.len_playlist = len(self.Playlist)
        self.track_path = self.Playlist[self.num_track]
        self.track_name = self.track_path[self.track_path.rfind('/') + 1:]

        self.initPlayer(self.track_path)

        if self.Player.IsPlaying():
            self.music_slider_update()

        self.is_looped = False

        self.color_bg = "#292133"
        self.frame_color = "#181d29"
        self.text_color = "#98fc03"
        self.button_color = "#ef81e6"

        self.but_name_01 = 'images/button_play.png'
        self.but_name_02 = 'images/button_next.png'
        self.but_name_03 = 'images/button_prev.png'
        self.but_name_04 = 'images/button_tc.png'

        self.l_sound_icon = 'images/loud_sound.png'
        self.q_sound_icon = 'images/quiet_sound.png'

        self.parent.title("MusREPL Audioplayer GUI")
        self.parent.geometry("420x330")
        self.parent.iconbitmap('images/icon.ico')
        self.parent.configure(background=self.color_bg)
        self.parent.resizable(width=False, height=False)

        self.but_play_open = ImageTk.PhotoImage(file=self.but_name_01)
        self.but_play = Button(self.parent, image=self.but_play_open, bg=self.color_bg, borderwidth=0, activebackground=self.color_bg,
                               command=self.play_pause, relief=FLAT)
        self.but_play.place(x=180, y=208)

        self.but_next_open = ImageTk.PhotoImage(file=self.but_name_02)
        self.but_next = Button(self.parent, image=self.but_next_open, bg=self.color_bg, activebackground=self.color_bg, borderwidth=0,
                               command=self.next_track, relief=FLAT)
        self.but_next.place(x=250, y=208)

        self.but_prev_open = ImageTk.PhotoImage(file=self.but_name_03)
        self.but_prev = Button(self.parent, image=self.but_prev_open, bg=self.color_bg, activebackground=self.color_bg, borderwidth=0,
                               command=self.prev_track, relief=FLAT)
        self.but_prev.place(x=80, y=208)

        self.Track = StringVar()
        self.Track.set(self.track_name)
        self.label = Label(self.parent, bg=self.frame_color, fg=self.text_color, textvariable=self.Track, relief='raised', font="Arial 17", height=2,
                           width=28)
        self.label.place(x=27, y=40)

        self.volume_slider = Scale(self.parent, from_=0, to=100, length=220, orient=HORIZONTAL, sliderlength=10, sliderrelief='flat',
                                   bg=self.button_color, activebackground=self.button_color, highlightbackground=self.color_bg,
                                   troughcolor=self.frame_color, bd=0, showvalue=0, width=10, command=self.volume_slide)

        self.volume_slider.set(self.Player.GetVolume())

        self.music_slider = Scale(self.parent, from_=0, to=self.track_time, length=230, orient=HORIZONTAL, sliderlength=10, sliderrelief='flat',
                                  bg=self.button_color, activebackground=self.button_color, highlightbackground=self.color_bg,
                                  troughcolor=self.frame_color, bd=0, showvalue=0, width=10)

        self.min_code = Entry(self.parent, bd=1, bg=self.frame_color, relief='flat', fg=self.text_color, font="Arial 15", justify=RIGHT, width=2)
        self.min_code.place(x=165, y=157)

        self.d_points = Label(self.parent, bd=1, bg=self.frame_color, relief='flat', fg=self.text_color, text=":", font="Arial 15", width=0)
        self.d_points.place(x=190, y=157)

        self.sec_code = Entry(self.parent, bd=1, bg=self.frame_color, relief='flat', fg=self.text_color, font="Arial 15", width=2)
        self.sec_code.place(x=200, y=157)

        self.but_tc_open = ImageTk.PhotoImage(file=self.but_name_04)
        self.but_tc = Button(self.parent, image=self.but_tc_open, bg=self.color_bg, activebackground=self.color_bg, borderwidth=1, relief=FLAT,
                             command=self.music_slide)
        self.but_tc.place(x=235, y=155)

        self.volume_slider.place(x=95, y=295)
        self.music_slider.place(x=90, y=130)

        self.Track_time = StringVar()
        self.Track_time.set("00:00")
        self.track_start = Label(self.parent, textvariable=self.Track_time, fg=self.text_color, font="Arial 14", bg=self.color_bg)
        self.track_start.place(x=32, y=121)

        self.Track_end = StringVar()
        self.Track_end.set(self.end_time)
        self.track_end = Label(self.parent, textvariable=self.Track_end, fg=self.text_color, font="Arial 14", bg=self.color_bg)
        self.track_end.place(x=328, y=121)

        self.loud_sound_icon = ImageTk.PhotoImage(file=self.l_sound_icon)
        self.loud_label = Label(self.parent, image=self.loud_sound_icon, bd=0)
        self.loud_label.place(x=330, y=282)

        self.quiet_sound_icon = ImageTk.PhotoImage(file=self.q_sound_icon)
        self.quiet_label = Label(self.parent, image=self.quiet_sound_icon, bd=0)
        self.quiet_label.place(x=42, y=285)

    def initPlayer(self, track_path):
        try:
            self.Player = SoundPlayer(track_path)

            self.track_time = int(self.Player.Duration())
            self.end_time = "{:02}:{:02}".format(self.track_time // 60, self.track_time % 60)
            self.Player.isvalid = True
        except:
            self.Player.isvalid = False

    def play_pause(self):
        if self.Player.IsPlaying():
            self.Player.Pause()
        else:
            self.Player.Start()
            self.music_slider_update()

    def next_track(self):
        self.Player.isended = True
        was_played = self.Player.IsPlaying()
        prev_volume = self.Player.GetVolume()
        start_again = False
        if self.num_track + 1 < self.len_playlist:
            self.num_track += 1
        elif self.is_looped:
            self.num_track = 0
            start_again = True
        else:
            self.num_track = 0

        self.track_path = self.Playlist[self.num_track]
        self.track_name = self.track_path[self.track_path.rfind('\\') + 1:]
        self.Track.set(self.track_name)
        self.initPlayer(self.track_path)
        self.music_slider_update()
        self.Track_end.set(self.end_time)
        self.Player.SetVolume(prev_volume)
        if start_again and was_played:
            self.Player.Play()

        if was_played and self.num_track:
            self.Player.Play()

    def prev_track(self):
        self.Player.isended = True
        was_played = self.Player.IsPlaying()
        prev_volume = self.Player.GetVolume()
        start_again = False
        if self.num_track - 1 >= 0:
            self.num_track -= 1
        elif self.is_looped:
            self.num_track = self.len_playlist - 1
            start_again = True

        self.track_path = self.Playlist[self.num_track]
        self.track_name = self.track_path[self.track_path.rfind('\\') + 1:]
        self.Track.set(self.track_name)
        self.initPlayer(self.track_path)
        self.Track_end.set(self.end_time)
        self.music_slider_update()
        self.Player.SetVolume(prev_volume)
        if start_again and was_played:
            self.Player.Play()

        if was_played and self.num_track != self.len_playlist - 1:
            self.Player.Play()

    def volume_slide(self, volume):
        self.Player.SetVolume(int(volume))

    def music_slide(self):
        time = None
        if self.sec_code.get().isdigit() and int(self.sec_code.get()) < 60:
            seconds = int(self.sec_code.get())
        else:
            seconds = None
        if self.min_code.get().isdigit():
            minutes = int(self.min_code.get())
        else:
            minutes = None
        self.sec_code.delete(0, END)
        self.min_code.delete(0, END)

        if seconds is not None and minutes is not None:
            time = minutes * 60 + seconds
        elif seconds is not None:
            time = seconds
        elif minutes is not None:
            time = minutes * 60

        if time is not None:
            self.Player.SetCurTime(int(time))
            self.Track_time.set("{:02}:{:02}".format(int(self.Player.CurrentTime()) // 60, int(self.Player.CurrentTime()) % 60))
            self.music_slider.set(self.Player.CurrentTime())

    def music_slider_update(self):
        self.music_slider.set(self.Player.CurrentTime())
        self.Track_time.set("{:02}:{:02}".format(int(self.Player.CurrentTime()) // 60, int(self.Player.CurrentTime()) % 60))
        if self.Player.IsPlaying():
            self.parent.after(1000, self.music_slider_update)

    def loop(self):
        self.is_looped = True

    def loop_off(self):
        self.is_looped = False
