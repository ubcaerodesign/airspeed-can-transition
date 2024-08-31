function [difference] = difference(table1,table2)
    %table 1 and table 2 must have the same size
    for n = 1 : length(table1)
        difference(n) = table1(n) - table2(n);
    end
    difference = difference';
end

