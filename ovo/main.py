import os
import random
import pygame

class Ovochschevoz():
    currentSong = None

    def nextSong(self):
        if self.currentSong:
            print(self.currentSong)
            print('-------------------')
            print()

        self.currentSong = self.current_list.pop(0)
        pygame.mixer.music.load(os.path.join(self.directory, self.currentSong))
        self.isPlaying = False
        self.length = 1
        self.startTime = random.randint(0, 60)
        self.timer = 0
        self.setTitle()
        
    def setTitle(self):
        self.title = self.font.render(f'{round(self.timer / 1000, 1)} / {self.length}', True, (255, 255, 0))

    def play(self, later = None):
        pygame.mixer.music.rewind()
        pygame.mixer.music.play()
        if later is None:
            pygame.mixer.music.set_pos(self.startTime)
        else:
            pygame.mixer.music.set_pos(self.startTime + self.length)

        self.isPlaying = True

    def stop(self):
        if self.isPlaying:
            self.isPlaying = False
            self.timer = 0
            pygame.mixer.music.stop()

    def increase(self):
        self.length += 1
        self.setTitle()

    def decrease(self):
        if self.length > 1:
            self.length -= 1
            self.setTitle()

    def __init__(self):
        self.title = ''
        self.directory = '/home/igorjan/documents/music'
        play_list = [f for f in os.listdir(self.directory) if f.endswith('.mp3')]
        self.current_list = play_list[:]
        random.shuffle(self.current_list)

        pygame.init()
        pygame.mixer.music.set_volume(0.1)
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
                if event.type == pygame.KEYDOWN and event.unicode:
                    if event.unicode == ' ':
                        if not self.isPlaying:
                            self.play()
                    elif event.unicode == '$':
                        if not self.isPlaying:
                            self.play(True)
                    elif event.unicode == '+':
                        if not self.isPlaying:
                            self.increase()
                    elif event.unicode == '-':
                        if not self.isPlaying:
                            self.decrease()
                    elif event.unicode == '@':
                        if not self.isPlaying:
                            self.nextSong()
                    else:
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
