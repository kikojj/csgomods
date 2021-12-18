import React from "react";
import ClickAwayListener from "react-click-away-listener";
import { Picker } from "./Picker";
import { useStyles } from "./styles";

export type ColorRGBA = {
  r: number;
  g: number;
  b: number;
  a: number;
};

export type ColorPickerProps = {
  color?: ColorRGBA;
  onChange?: (v: ColorRGBA) => void;
};
export const ColorPicker: React.FC<ColorPickerProps> = ({
  color: _color,
  onChange,
}) => {
  const [show, setShow] = React.useState<boolean>(false);
  const [color, setColor] = React.useState<ColorRGBA>({
    r: 0,
    g: 0,
    b: 0,
    a: 255,
    ..._color,
  });

  const classes = useStyles({ color });

  const onClickAway = React.useCallback(() => {
    setShow(false);
    onChange && onChange({ ...color });
  }, [color, setShow, onChange]);

  return (
    <div className={classes.container}>
      <div className={classes.colorContainer} onClick={() => setShow(true)} />
      {show && (
        <ClickAwayListener onClickAway={onClickAway}>
          <div className={classes.pickerContainer}>
            <Picker color={color} onChange={setColor} />
          </div>
        </ClickAwayListener>
      )}
    </div>
  );
};
