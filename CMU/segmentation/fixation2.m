function fixation2(input_dir, starti, endi)

if ~exist('input_dir', 'var')
    disp('No input_dir...')
    return;
end

output_dir=[input_dir, '/output'];
if(~exist(output_dir, 'dir'))
    mkdir(output_dir);
end

fix_dir=[output_dir, '/fix'];
if(~exist(fix_dir, 'dir'))
    mkdir(fix_dir);
end

filenames=dir([input_dir, '/*.ppm']);
if(length(filenames)==0)
    filenames=dir([input_dir, '/*.jpg']);
end
if(length(filenames)==0)
    filenames=dir([input_dir, '/*.png']);
end

N=length(filenames);

if ~exist('starti', 'var')
    starti = 1;    
elseif ischar(starti)
    starti = str2num(starti);
end

if ~exist('endi', 'var')
    endi = N;   
elseif ischar(endi)
    endi = str2num(endi);    
end

eye_pos_txt=fullfile(input_dir, 'eye_positions.txt');
grid=[-50,0 ; 0,-50 ; 0,0 ; 0,50 ; 50,0];
eye_pos=load(eye_pos_txt);

for i=starti:endi,    
    imgFileName=fullfile(input_dir, filenames(i).name);
    
    disp(imgFileName);

    [pathstr, name, ext] = fileparts(imgFileName);
    
    fix_txt = [name, '_fix.txt'];
    fid = fopen(fullfile(fix_dir,fix_txt),'w');
    fprintf(fid,'%f %f\n',(ones(size(grid,1),1)*eye_pos(i,:)+grid)');
    fclose(fid);
end
end