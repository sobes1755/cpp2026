angle = pi;
axis = (0, 0, 1);

c = cos(angle/2);
s = sin(angle/2);

q = (c, s * axis.x, s * axis.y, s * axis.z);
qconj = conjugate(q);

println(q);
println(qconj);

v = (1, 0, 0);
vq = (0, v.x, v.y, v.z);
wq = q * vq * qconj;
w = (wq.x, wq.y, wq.z);

println(v);
println(w);
