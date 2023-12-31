import pygame


pygame.init()

window = pygame.display.set_mode((320, 300))

pygame.display.set_caption("Temple of Infinity Glove")

x = 153
y = 90

run = True
action = False
FRAMES = 60

Backgrounds = [pygame.image.load("Спрайты для лабы/Temple/temple_start.png"),
               pygame.image.load("Спрайты для лабы/Temple/temple_fight.png"),
               pygame.image.load("Спрайты для лабы/Temple/temple_end.png")]

Grass = pygame.image.load("Спрайты для лабы/Grass.png")

Win = pygame.image.load("Спрайты для лабы/Hero/win.png")

Chest = [pygame.image.load("Спрайты для лабы/chest/chest_open.png"),
         pygame.image.load("Спрайты для лабы/chest/chest_close.png")]

# Animations for Hero
Stay = pygame.image.load("Спрайты для лабы/Hero/hero_stay.png")

H_Walk = [pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_01.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_02.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_03.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_04.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_05.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_06.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_07.png"),
          pygame.image.load("Спрайты для лабы/Hero/Hero_walk/hero_walk_08.png")]

H_Attack = [
    pygame.image.load("Спрайты для лабы/Hero/Hero_attack/hero_attack_01.png"),
    pygame.image.load("Спрайты для лабы/Hero/Hero_attack/hero_attack_02.png"),
    pygame.image.load("Спрайты для лабы/Hero/Hero_attack/hero_attack_03.png"),
    pygame.image.load("Спрайты для лабы/Hero/Hero_attack/hero_attack_04.png"),
    pygame.image.load("Спрайты для лабы/Hero/Hero_attack/hero_attack_05.png")]

# Animations for Guardian
G_Stay = pygame.image.load("Спрайты для лабы/Guardian/guardian_stay.png")

G_Walk = [
    pygame.image.load("Спрайты для лабы/Guardian/Walk/guardian_walk_01.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Walk/guardian_walk_02.png")]

G_Attack = [
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_01.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_02.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_03.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_05.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_06.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_07.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_19.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_20.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_21.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_22.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_23.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_24.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_25.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_26.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_27.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_28.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_29.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_30.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_31.png"),
    pygame.image.load("Спрайты для лабы/Guardian/Attack/guardian_attack_32.png")]

G_Death = [
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-0-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-1-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-2-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-3-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-4-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-5-0.png"),
    pygame.image.load("Спрайты для лабы/death_effects/death-effects-6-0.png")]

clock = pygame.time.Clock()

hero_walk = False
hero_punch = False

g_walk = False
g_attack = False
g_stay = True

bg = 0

animCount_h = 0
animCount_g = 0
h_step = 1

g_x = 150
g_y = 35
g_step = 1

g_punched = False
h_punched = False

scene = 0

while run:
    clock.tick(FRAMES)

    if bg == 0:
        window.blit(Grass, (0, 0))
        window.blit(Backgrounds[bg], (40, 0))
    elif bg == 1 and action:
        window.fill((0, 0, 0))
        window.blit(Backgrounds[bg], (0, 0))
        if g_stay:
            window.blit(G_Stay, (g_x, g_y))
    elif bg == 2 and action:
        window.fill((0, 0, 0))
        window.blit(Backgrounds[bg], (95, 70))
        window.blit(Chest[1], (145, 95))

    if not action and not bg:
        window.blit(Stay, (x, y))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_SPACE]:
        action = True
    elif keys[pygame.K_r]:  # Replay
        window.fill((0, 0, 0))
        hero_walk = False
        hero_punch = False
        g_walk = False
        g_attack = False
        g_stay = True
        bg = 0
        animCount_h = 0
        animCount_g = 0
        h_step = 1
        g_x = 150
        g_y = 35
        g_step = 1
        g_punched = False
        h_punched = False
        scene = 0
        action = False
        x = 153
        y = 90

    if action:
        if not bg:
            hero_walk = True

        if animCount_h + 1 >= FRAMES:
            animCount_h = 0

        if animCount_g + 1 >= FRAMES:
            animCount_g = 0

        if hero_walk:
            window.blit(H_Walk[animCount_h // 8], (x, y))
            animCount_h += 1
            y -= h_step

        if hero_punch:
            window.blit(H_Attack[animCount_h // 12], (x, y))
            animCount_h += 1

        if g_attack:
            window.blit(G_Attack[animCount_g // 3], (g_x, g_y))
            animCount_g += 1
            g_y += g_step
        elif g_walk:
            window.blit(G_Walk[animCount_g % 2], (g_x, g_y))
            animCount_g += 1
            g_y += g_step

        if g_punched:
            window.blit(G_Death[animCount_g // 9], (g_x, g_y))
            animCount_g += 1

        if bg == 1:
            if scene == 0:
                g_walk = False
                g_attack = True
                if g_y >= 135:
                    g_walk = True
                    g_attack = False
                    h_punched = True
                    g_step = 1
                    scene = 1
            elif scene == 1:
                if y < 225:
                    h_step = -2
                else:
                    h_step = 1
                    scene += 1
                    hero_walk = False
                    hero_punch = True
                    scene = 2
            elif scene == 2:
                if g_y >= 205:
                    g_walk = False
                    g_punched = True
                    hero_punch = False
                if g_punched:
                    hero_walk = True
                    if y <= 180:
                        g_punched = False

        if y <= 40 and not bg:
            bg += 1
            y = 265
            g_stay = False
            g_attack = True
            g_step = 3
            h_step = 3
        elif y <= 20 and bg == 1:
            bg += 1
            y = 150
            h_step = 1
        elif y <= 115 and bg == 2:
            action = False
            window.fill((0, 0, 0))
            window.blit(Backgrounds[bg], (95, 70))
            window.blit(Chest[0], (145, 95))
            window.blit(Win, (x, y - 7))

    pygame.display.update()

pygame.quit()
