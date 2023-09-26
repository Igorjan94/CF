import os
import random
import pygame

class Ovochschevoz():
    currentSong = None
    isStarted = None

    def nextSong(self):
        if self.currentSong and self.isStarted:
            print(self.currentSong)
            print('-------------------')
            print()

        self.currentSong = self.current_list.pop(0)
        pygame.mixer.music.load(os.path.join(self.directory, self.currentSong))
        self.isPlaying = False
        self.isStarted = False
        self.length = 1
        self.startTime = random.randint(0, 60)
        self.timer = 0
        self.setTitle()
        
    def setTitle(self):
        self.title = self.font.render(f'{round(self.timer / 1000, 1)} / {self.length}', True, (255, 255, 0))

    def pause(self):
        self.isPlaying = False
        pygame.mixer.music.pause()

    def unpause(self):
        self.isPlaying = True
        if self.timer > 0:
            pygame.mixer.music.unpause()
        else:
            self.play()

    def play(self, later = None):
        pygame.mixer.music.rewind()
        pygame.mixer.music.play()
        if later is None:
            pygame.mixer.music.set_pos(self.startTime)
        else:
            pygame.mixer.music.set_pos(self.startTime + self.length)
            self.timer = self.length * 1000
            self.length *= 2

        self.isPlaying = True
        self.isStarted = True

    def stop(self):
        if self.isPlaying:
            self.isPlaying = False
            self.timer = 0
            pygame.mixer.music.stop()

    def increase(self, mul = False):
        if mul:
            self.length *= 2
        else:
            self.length += 1
        self.setTitle()

    def decrease(self):
        if self.length > 1:
            self.length -= 1
            self.setTitle()

    def updateVolume(self, diff):
        self.volume = min(1, max(0, self.volume + diff))
        pygame.mixer.music.set_volume(self.volume)

    def __init__(self):
        self.title = ''
        self.directory = '/home/igorjan/documents/music'
        self.volume = 0.1

        play_list = [f for f in os.listdir(self.directory) if f.endswith('.mp3')]
        self.current_list = play_list[:]
        random.shuffle(self.current_list)

        pygame.init()
        self.updateVolume(0)
        self.window = pygame.display.set_mode((800, 100))
        self.font = pygame.font.SysFont(None, 40)
        self.clock = pygame.time.Clock()

        window_center = self.window.get_rect().center

        self.nextSong()

        run = True
        while run:
            t = self.clock.tick(100)
            if self.isPlaying:
                self.timer += t
                self.setTitle()
                if self.timer >= self.length * 1000:
                    self.stop()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.unicode == ' ':
                        if self.isPlaying:
                            self.pause()
                        else:
                            self.unpause()
                    elif event.unicode == '$' or event.unicode == '4':
                        if not self.isPlaying:
                            self.play(True)
                    elif event.unicode == '*' or event.unicode == '8':
                        self.increase(True)
                    elif event.unicode == '+' or event.unicode == '=' or event.scancode == 79: # right
                        self.increase()
                    elif event.unicode == '-' or event.scancode == 80: # left
                        self.decrease()
                    elif event.unicode == '@' or event.unicode == '2':
                        if not self.isPlaying:
                            self.nextSong()
                    elif event.scancode == 81: # down
                        self.updateVolume(-0.05)
                    elif event.scancode == 82: # up
                        self.updateVolume(+0.05)
                    elif event.unicode:
                        print(event.unicode)
                        self.stop()

                if event.type == pygame.QUIT:
                    self.nextSong()
                    run = False
            

            self.window.fill(0)
            if self.title:
                self.window.blit(self.title, self.title.get_rect(center = window_center))
            pygame.display.flip()
            
        pygame.quit()
        exit()

if __name__ == '__main__':
    Ovochschevoz()
