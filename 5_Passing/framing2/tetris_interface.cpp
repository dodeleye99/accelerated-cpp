#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "char_pic.h"
#include "tetris_interface.h"

using std::string;
using std::vector;


// converts an integer to a string, and pads it with leading zeros to make it display with a given minimum number of digits.
string padded_int(const int value, const int pad)
{
    // we use a stringstream to write the integer value on.
    std::stringstream ss;
    
    // use setw() to make the stream consist of a given number of (blank) characters by default. 
    // use setfill() to fill these blanks with zeros.
    // finally write the value onto the stream.
    ss << std::setw(pad) << std::setfill('0') << value;

    // return the string that we have written on the stream.
    return ss.str();
}

// the section of the interface containing the number of lines that have been cleared.
vector<string> lines_panel(const int lines)
{
    const string::size_type space = 2;
    const int digits = 3;
    
    // form the text (only one line), ensuring space between the label and the (zero-padded) lines value
    const string lines_text = "LINES CLEARED" + string(space, ' ') + padded_int(lines, digits);

    // construct the panel, then frame it
    vector<string> panel;
    panel.push_back(lines_text);
    
    return frame(panel);
}

// the section of the interface containing the current score and the high score
vector<string> score_panel(const int score, const int high_score)
{    
    const int digits = 6;
    
    const string high_score_label = "HIGH SCORE";
    const string score_label = "SCORE";

    // ensure the score values display a fixed minimum number of digits (leading zeros) by default.
    const string high_score_value = padded_int(high_score, digits);
    const string score_value = padded_int(score, digits);

    // construct the panel, then frame it
    vector<string> panel;
    panel.push_back(high_score_label);
    panel.push_back(high_score_value);
    panel.push_back("");
    panel.push_back(score_label);
    panel.push_back(score_value);
    panel.push_back("");
    
    return frame(panel);
}

// the section of the interface containing of the next piece to enter the grid.
// we will leave its contents blank, only showing the label.
vector<string> next_panel()
{    
    const int height = 8;
    const string next_label = "NEXT PIECE";

    // mark vertical gaps to fix a height
    const vector<string> gaps(height - 1, "");

    // construct the panel, then frame it
    vector<string> panel;
    panel.push_back(next_label);
    panel = vcat(panel, gaps);
    
    return frame(panel);
}

// the section of the interface containing of the current speed level.
vector<string> level_panel(const int level)
{    
    const string::size_type width = 10;
    const int digits = 2;

    const string level_label = "LEVEL";
    const string gap(width, ' ');
    // ensure the level value displays a fixed minimum number of digits (leading zeros) by default.
    const string level_value = padded_int(level, digits);

    // construct the panel, then frame it
    vector<string> panel;
    panel.push_back(level_label);
    panel.push_back(gap);
    panel.push_back(level_value);
    
    return frame(panel);
}

// the section of the interface containing of the grid.
// we will leave it blank, only showing the text "TETRIS".
vector<string> grid_panel()
{    
    const string::size_type half_width = 9;
    const int height = 18;
    const string grid_text = "TETRIS";
    
    // ensure the displayed text is on the top row, centered.
    const string::size_type label_size = grid_text.size();
    const string hz_pad(half_width - label_size/2, ' ');
    const string grid_label = hz_pad + grid_text + hz_pad;

    // mark vertical gaps to fix a height
    const vector<string> v_gap(height-1, " ");
    
    // construct the panel, then frame it
    vector<string> panel;
    panel.push_back(grid_label);
    panel = vcat(panel, v_gap);
    
    return frame(panel);
}

// build the interface.
vector<string> build_interface()
{
    // The interface will have the following layout:
    // (LEFT)    (RIGHT)
    // <lines> | <scores>
    // <grid>  | <next>
    //         | <level>

    vector<string> left;
    vector<string> right;
    vector<string> interface;

    // the left half of the interface
    const vector<string> lines = lines_panel(0);
    const vector<string> field = grid_panel();
    left  = vcat(lines, field);

    // the right half of the interface
    const vector<string> scores = score_panel(0, 223375);
    const vector<string> next = next_panel();
    const vector<string> level = level_panel(1);
    right = vcat(scores, next);
    right = vcat(right, level);

    // construct the whole interface by joining the half-sections horizontally, and then frame it.
    interface = hcat(left, right);
    
    return frame(hcat(left, right));
}