import React from "react";
import { Range as ReactRange } from "react-range";
import { join, useProvidableState } from "@components/utils";
import { colors } from "@utils";
import { Track } from "./Track";
import { useStyles } from "./styles";

export type RangeProps = {
  className?: string;
  type?: "int" | "float";
  value?: number;
  min?: number;
  max?: number;
  step?: number;
  color?: string;
  onChange?: (value: number) => void;
  onClick?: (
    e: React.MouseEvent<HTMLDivElement, globalThis.MouseEvent>
  ) => void;
};
export const Range: React.FC<RangeProps> = ({
  className,
  value: _value,
  onChange: _onChange,
  type = "int",
  min = 0,
  max = 100,
  step = 1,
  color = colors.primary,
  onClick,
}) => {
  const [value, onChange] = useProvidableState(min, _value, _onChange);

  const classes = useStyles({ type });

  const valueInPercents = ((value - min) / (max - min)) * 100;
  const renderAdditionalButtons = type === "float";

  const onMinusClick = React.useCallback(
    () => onChange(value - step < min ? min : value - step),
    [min, step, value, onChange]
  );

  const onPlusClick = React.useCallback(
    () => onChange(value + step > max ? max : value + step),
    [max, step, value, onChange]
  );

  const onRangeChange = React.useCallback(
    (values: number[]) => onChange(values[0]),
    [onChange]
  );

  return (
    <div className={join(classes.container, className)} onClick={onClick}>
      {renderAdditionalButtons && (
        <button className={classes.btn_minus} onClick={onMinusClick}>
          -
        </button>
      )}
      <div className={classes.content}>
        <ReactRange
          values={[value]}
          step={step}
          min={min}
          max={max}
          onChange={onRangeChange}
          renderTrack={(props) => (
            <Track color={color} valueInPercents={valueInPercents} {...props} />
          )}
          renderThumb={({ props }) => (
            <div {...props} className={classes.valueMark} />
          )}
        />
      </div>
      {renderAdditionalButtons && (
        <button className={classes.btn_plus} onClick={onPlusClick}>
          +
        </button>
      )}
    </div>
  );
};
