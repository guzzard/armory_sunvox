let project = new Project('sunvox', __dirname);

project.addFile('cpp/sunvox/**');
project.addIncludeDir('cpp/sunvox');

resolve(project);
