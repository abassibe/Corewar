.name "tst"
.comment "tsts"

label3:
live %:label1
ld :label2,r1
st r1,:label3
label2: add r1,r2,r3
sub r2,r3,r4
label1: and %:label3,%:label4,r1
or %:label3,%:label1,r4
xor %:label4,%:label2,r5
zjmp %16
ldi %:label4,%:label1,r16
label4: sti r12,%:label3,%:label3
fork %:label3
lld 15,r13
lldi r14,r12,r2
lfork %165
aff r15
