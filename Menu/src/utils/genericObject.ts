export class GenericObject {
    static keys<KeyType extends PropertyKey = PropertyKey, ValueType = unknown>(object: { [T in KeyType]?: ValueType }) {
        return Object.keys(object) as KeyType[];
    }
}