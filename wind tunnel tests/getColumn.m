function [column_save] = getColumn(csv_file, column_number)
    tb = readtable(csv_file);
    col = cast(tb{:,column_number}, "double");
    column_save = col;
end
