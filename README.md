## Adventure RPG
Top-down adventure game written in C++

Uses SDL2, and SDL2\_ttf libraries for rendering to the screen


### Checklist 
- [X] Create basic main menu with some options that call other menus with options
    - [X] Test options
    - [X] Get fonts working
- [X] Update rendering
    - [X] Use actual renderer
    - [X] Implement Alpha Channels
    - [X] Get text rendering
- [X] Have KeyboardHandler give navigation capabilities to menu
- [X] Verify that alpha is either 0=invis, 255=vis or vice versa
- [ ] Figure out how to input text for names / output text to display 
- [ ] Create Interactive Friendly NPCs
    - [X] Create other character NPCs
    - [X] Figure out how to speak to them (respecting a specific individual in crowded area, and not being random)
- [ ] Revamp the gameloop to have consistent parallel physics
    - [ ] Separate render and update threads
    - [ ] Somewhat multithread the program (at least get htop to read that multiple cores are being saturated)
- [ ] Brainstorm Fights 
    - [ ] Brainstorm how/where fights should begin
        - [ ] Pokemon-esque Tall-grass? Actual people?
    - [ ] Create Non-Friendly NPCs
- [ ] Evaluate whether Tensorflow is feasible for ANYTHING
- [ ] Inventory
    - [ ] Brainstorm Inventory
- [ ] Square Grid with keyboard navigation (probably mouse too)
    - [ ] User Inventory (visual at least)
    - [ ] User Inventory (interactive)
        - [ ] Equip / Use / Drop 
- [ ] Equipments
    - [ ] Brainstorm Equipments
    - [ ] User Equipment (visual at least)
    - [ ] User Equipment (interactive)
- [ ] Implement Trade
    - [ ] Shops
    - [ ] Currency / Buying / Selling
- [ ] Implement Saving / Loading
- [ ] Write story
    - [ ] Create more maps
    - [ ] Win / Loss conditions

