% Read in data
data = importdata('train.txt', ' ');
disp('Done train');
test = importdata('qual.dta', ' ');

disp('Done Read');
Xtrain = data(:, 1:2);
Ytrain = data(:, 3);
test = test(:, 1:2);

disp('Finished separating');

layers = [ ...
    sequenceInputLayer(2)
    lstmLayer(5000,'OutputMode','sequence')
    lstmLayer(1000,'OutputMode','sequence')
    fullyConnectedLayer(5)
    softmaxLayer
    classificationLayer];

options = trainingOptions('adam', ...
    'ExecutionEnvironment','cpu', ...
    'MaxEpochs', 1, ...
    'MiniBatchSize',1000, ...
    'GradientThreshold',1, ...
    'Verbose',0, ...
    'Plots','training-progress');

disp('finished creating')
Ytrain = categorical(Ytrain);
net = trainNetwork(Xtrain,Ytrain,layers,options);

disp('finished training');

YPred = classify(net, test,'MiniBatchSize', 200);

disp('finished predicting');

fileID = fopen('lstm.txt','w');
fprintf(fileID,'%6.2f\n', YPred);
fclose(fileID);

