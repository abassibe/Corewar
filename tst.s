.name "test"
.comment "test"

	 fork  %:label00          		# 3,0,281
	 ld    %-272,r3           		# 7,3,278
	 live  %0                 		# 5,10,271
	 fork  %:label01          		# 3,15,266
	 ld    %-272,r3           		# 7,18,263
	 fork  %:label02          		# 3,25,256
	 ld    %0,r2              		# 7,28,253
	 ld    %0,r4              		# 7,35,246
	 zjmp  %:label03          		# 3,42,239

label02: ld    %4,r2              		# 7,45,236
	 ld    %0,r4              		# 7,52,229
	 zjmp  %:label03          		# 3,59,222

label01: ld    %-202,r3           		# 7,62,219
	
	label00:
	label03:
