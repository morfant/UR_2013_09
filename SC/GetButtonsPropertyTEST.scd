~buts[0, 0];
(
~win = Window.new("Get button's property TEST", Rect(0, 500, 100, 100));
~bt = Button(~win, Rect(10, 10, 50, 50));
//~sld = Slider(~bt, Rect(0, 0, 50, 20));
~sld2 = Slider(~win, Rect(~bt.bounds.left, ~bt.bounds.top - 15, 80, 20));

~bt.bounds.left.postln;
~win.front;
)