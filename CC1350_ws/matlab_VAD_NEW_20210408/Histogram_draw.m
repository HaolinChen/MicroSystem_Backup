close all;
figure();
data = [0.8767 0.8333 0.8481 0.8356 0.8824];
b = bar(data);
ch = get(b,'children');
set(gca,'XTickLabel',{'Dataset 1','Dataset 2','Dataset 3','Dataset 4','Dataset 5'})
ylim([0.7,1]);
grid on;
ax = gca;
ax.GridColor = [0 .5 .5];
ax.GridLineStyle = '--';
ax.GridAlpha = 0.5;
ax.Layer = 'top';
ylabel('True Positive Rate');
title('CC1350 SED Algorithm Test');