import React from "react";

import { ChromePicker, ColorResult, RGBColor } from "react-color";
import { ClickAwayListener, Radio as _Radio } from "@material-ui/core";
import { useStyles } from "./styles";
import { TMargin } from "@utils";

export type ColorPickerProps = {
  label: string;
  marginTop?: TMargin;
  value?: RGBColor;
  onChange?: (color: RGBColor, event: React.ChangeEvent<HTMLInputElement>) => void;
};
export const ColorPicker: React.FC<ColorPickerProps> = ({
  label,
  marginTop,
  value = { r: 0, g: 0, b: 0, a: 255 },
  onChange,
}) => {
  const classes = useStyles({ marginTop, color: value });
  const [show, setShow] = React.useState<boolean>(false);
  return (
    <div className={classes.colorPicker} style={{ marginTop }}>
      <h5 className={classes.colorPicker_label}>{label}</h5>
      <div className={classes.colorPicker_value} onClick={() => setShow(true)}>
        {show ? (
          <ClickAwayListener onClickAway={() => setShow(false)}>
            <ChromePicker
              className={classes.colorPicker_picker}
              color={{ ...value, a: (value.a || 0) / 255 }}
              onChange={(c, e) => onChange && onChange({ ...c.rgb, a: (c.rgb.a || 0) * 255 }, e)}
            />
          </ClickAwayListener>
        ) : (
          ""
        )}
      </div>
    </div>
  );
};
