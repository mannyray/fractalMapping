function createMappings(fileName,level_count)
	X = imread(fileName);


	level_count = str2num(level_count);
	%empty files:
	dlmwrite('v.txt','','delimiter','');
	dlmwrite('d.txt','','delimiter','');
	dlmwrite('h.txt','','delimiter','');
	dlmwrite('a.txt','','delimiter','');

	[c,s]=wavedec2(X,level_count,'haar');%also can use haar
	for i = level_count:-1:1
		 [H,V,D] = detcoef2('all',c,s,i);
		 A = appcoef2(c,s,'haar',i);
		 
		 dlmwrite('v.txt',char(10),'-append','delimiter',' ');
		 dlmwrite('h.txt',char(10),'-append','delimiter',' ');
		 dlmwrite('d.txt',char(10),'-append','delimiter',' ');
		 if i == level_count
		 	dlmwrite('a.txt',char(10),'-append','delimiter',' ');
	 	 end
		 
		 
		 dlmwrite('v.txt',i,'-append','delimiter',' ');
		 dlmwrite('h.txt',i,'-append','delimiter',' ');
		 dlmwrite('d.txt',i,'-append','delimiter',' ');
		 if i == level_count
		 	dlmwrite('a.txt',i,'-append','delimiter',' ');  
	 	 end
		 
		 
		 dlmwrite('v.txt', size(V),'-append','delimiter',' ');
		 dlmwrite('h.txt',size(H),'-append','delimiter',' ');
		 dlmwrite('d.txt',size(D),'-append','delimiter',' ');
		 if i == level_count
		 	dlmwrite('a.txt',size(A),'-append','delimiter',' ');
	 	 end
		 
		 
		 %garbage variable so that writing and reading from file is easier 
		 dlmwrite('v.txt',i,'-append','delimiter',' ');
		 dlmwrite('h.txt',i,'-append','delimiter',' ');
		 dlmwrite('d.txt',i,'-append','delimiter',' ');
		 if i == level_count
		 	dlmwrite('a.txt',i,'-append','delimiter',' ');
	 	 end
		 	 
		 
		 dlmwrite('v.txt',V,'-append','delimiter',' ');
		 dlmwrite('h.txt',H,'-append','delimiter',' ');
		 dlmwrite('d.txt',D,'-append','delimiter',' ');
		 if i == level_count
		 	dlmwrite('a.txt',A,'-append','delimiter',' ');
	 	 end
	end
	exit
end
