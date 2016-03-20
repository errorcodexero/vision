function Trajectory
y0 = input("Where do you want to start?\n\n");
theta = input("What angle do you want to start at?\n\n");
v0 = input ("At which speed do you want to start?\n\n");

d = (((v0 .* cos(theta * pi / 180))./32.18504) .*(v0 .* sin (theta * pi / 180) .+ sqrt(pow2(v0 .* sin(theta * pi / 180), 2) .+ 2.*32.18504.*v0)));
if (d >= 10)
	x = 0:0.1:d;
	x1 = -10:0.001:d;
else
	x = 0:0.1:10;
	x1 = -10:0.001:10;
endif
x1 = 0:0.1:d;
y = y0 .+ x .* tan(theta * pi / 180) .- (((32.17 .* (x .* x) )/(2 .*((v0 .* cos(theta * pi / 180)).*(v0 .* cos(theta * pi ./ 180))))));
y(y<0) = [];
title ("Trajectory");
xlabel ("Feet - Distance");
ylabel ("Feet - Height");
comet(x,y,0.001);
xlim([0,d]);
ylim([0, 25]);
hold on;
%plot (0,x1);
hold off;
input ("Press any key to quit");
endfunction
